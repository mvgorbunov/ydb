#include "percentile_counter.h"

#include <ydb/library/persqueue/topic_parser/topic_parser.h>
#include <ydb/core/base/counters.h>

namespace NKikimr {

namespace NPQ {

NMonitoring::TDynamicCounterPtr GetCounters(NMonitoring::TDynamicCounterPtr counters,
                                            const TString& subsystem, const TString& topic)
{
    auto pos = topic.find("--");
    Y_VERIFY(pos != TString::npos);

    TString origDC = topic.substr(4, pos - 4);
    origDC.to_title();
    TString realTopic = topic.substr(pos + 2);
    pos = realTopic.find("--");
    TString producer = realTopic.substr(0, pos);
    TString topicPath = NPersQueue::ConvertOldTopicName(realTopic);
    TString account = topicPath.substr(0, topicPath.find("/"));
    return GetServiceCounters(counters, "pqproxy|" + subsystem)
        ->GetSubgroup("OriginDC", origDC)
        ->GetSubgroup("Producer", producer)
        ->GetSubgroup("TopicPath", topicPath)
        ->GetSubgroup("Account", account)
        ->GetSubgroup("Topic", realTopic);
}

NMonitoring::TDynamicCounterPtr GetCountersForStream(NMonitoring::TDynamicCounterPtr counters,
                                                     const TString& subsystem)
{
    return counters->GetSubgroup("counters", "pqproxy")
        ->GetSubgroup("subsystem", subsystem);
}

TVector<TLabelsInfo> GetLabels(const TString& topic)
{
    auto pos = topic.find("--");
    if (pos == TString::npos)
        return {};
    Y_VERIFY(pos != TString::npos);

    TString origDC = topic.substr(4, pos - 4);

    return GetLabels(origDC, topic.substr(pos + 2));
}
 
TVector<TLabelsInfo> GetLabels(const TString& cluster, const TString& realTopic)
{
    TString origDC = cluster;
    origDC.to_title();
    auto pos = realTopic.find("--");
    if (pos == TString::npos)
        return {};
    TString producer = realTopic.substr(0, pos);
    TString topicPath = NPersQueue::ConvertOldTopicName(realTopic);
    TString account = topicPath.substr(0, topicPath.find("/"));
    TVector<TLabelsInfo> res = {
            {{{"Account", account}}, {"total"}},
            {{{"Producer", producer}}, {"total"}},
            {{{"Topic", realTopic}, {"TopicPath", topicPath}}, {"total", "total"}},
            {{{"OriginDC", origDC}}, {"cluster"}}
        };
    return res;
}

TVector<TLabelsInfo> GetLabelsForStream(const TString& topic, const TString& cloudId,
                                        const TString& dbId, const TString& folderId) {
    TVector<TLabelsInfo> res = {
            {{{"database", dbId}}, {dbId}},
            {{{"cloud", cloudId}}, {cloudId}},
            {{{"folder", folderId}}, {folderId}},
            {{{"stream", topic}}, {topic}}};
    return res;
}

TMultiCounter::TMultiCounter(NMonitoring::TDynamicCounterPtr counters,
                             const TVector<TLabelsInfo>& labels,
                             const TVector<std::pair<TString, TString>>& subgroups,
                             const TVector<TString>& counter_names,
                             bool deriv,
                             const TString& name,
                             bool expiring)
    : Value(0)
{
    Y_VERIFY(counters);

    for (const auto& counter : counter_names) {
        for (ui32 i = 0; i <= labels.size(); ++i) {
            auto cc = counters;
            for (ui32 j = 0; j < labels.size(); ++j) {
                Y_VERIFY(!labels[j].Labels.empty());
                for (ui32 k = 0; k < labels[j].Labels.size(); ++k) {
                    Y_VERIFY(labels[j].Labels.size() == labels[j].AggrNames.size());
                    const TString& res = (j < i) ? labels[j].Labels[k].second : labels[j].AggrNames[k];
                    cc = cc->GetSubgroup(labels[j].Labels[k].first, res);
                }
            }
            for (const auto& g: subgroups) {
                cc = cc->GetSubgroup(g.first, g.second);
            }
            if (expiring) {
                Counters.push_back(cc->GetExpiringNamedCounter(name, counter, deriv));
            } else {
                Counters.push_back(cc->GetNamedCounter(name, counter, deriv));
            }
        }
    }
}

void TMultiCounter::Inc(ui64 val)
{
    for (auto& c : Counters) (*c) += val;
    Value += val;
}

void TMultiCounter::Dec(ui64 val) {
    for (auto& c : Counters) (*c) -= val;
    Value -= val;
}

void TMultiCounter::Set(ui64 value) {
    auto diff = value - Value;
    Inc(diff);
}

TMultiCounter::operator bool() {
    return !Counters.empty();
}


TPercentileCounter::TPercentileCounter(TIntrusivePtr<NMonitoring::TDynamicCounters> counters, const TVector<TLabelsInfo>& labels, const TVector<std::pair<TString, TString>>& subgroups, const TString& sensor,
                    const TVector<std::pair<ui64, TString>>& intervals, const bool deriv, bool expiring)
{
    Y_VERIFY(!intervals.empty());
    Counters.reserve(intervals.size());
    Ranges.reserve(intervals.size());
    for (auto& interval : intervals) {
        Ranges.push_back(interval.first);
        Counters.push_back(TMultiCounter(counters, labels, subgroups, {interval.second}, deriv, sensor, expiring));
    }
    Ranges.back() = Max<ui64>();
}

void TPercentileCounter::IncFor(ui64 key, ui64 value) {
    if (!Ranges.empty()) {
        ui32 i = 0;
        // The last range value is Max<ui64>().
        while (Ranges[i] < key) {
            ++i;
        }
        Y_ASSERT(i < Ranges.size());
        Counters[i].Inc(value);
    }
}

void TPercentileCounter::DecFor(ui64 key, ui64 value) {
    if (!Ranges.empty()) {
        ui32 i = 0;
        // The last range value is Max<ui64>().
        while (Ranges[i] < key) {
            ++i;
        }
        Y_ASSERT(i < Ranges.size());
        Counters[i].Dec(value);
    }
}

NKikimr::NPQ::TPercentileCounter CreateSLIDurationCounter(TIntrusivePtr<NMonitoring::TDynamicCounters> counters, TVector<NPQ::TLabelsInfo> aggr, const TString name, ui32 border, TVector<ui32> durations)
{
    bool found = false;
    for (auto it = durations.begin(); it != durations.end(); ++it) {
        if (*it == border) {
            found = true;
            break;
        }
        if (*it > border) {
            found = true;
            durations.insert(it, border);
            break;
        }
    }
    if (!found)
        durations.push_back(border);
    TVector<std::pair<ui64, TString>> buckets;
    for (auto& dur : durations) {
        buckets.emplace_back(dur, TStringBuilder() << dur << "ms");
    }
    return NKikimr::NPQ::TPercentileCounter(counters->GetSubgroup("sensor", name), aggr, {}, "Duration", buckets, true, false);
}



} // NPQ
} // NKikimr
