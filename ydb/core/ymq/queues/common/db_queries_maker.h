#pragma once

#include <ydb/core/ymq/base/queue_path.h>

#include <ydb/core/ymq/queues/fifo/queries.h>
#include <ydb/core/ymq/queues/std/queries.h>

#include <util/string/builder.h>
#include <util/string/printf.h>
#include <util/datetime/base.h>

namespace NKikimr::NSQS {

const char* const QUEUE_ID_KEYS_RANGE = R"__(
            '('QueueIdNumberHash queueIdNumberHash queueIdNumberHash)
            '('QueueIdNumber queueIdNumber queueIdNumber)
        )__";

const char* const QUEUE_ID_KEYS = R"__(
            '('QueueIdNumberHash queueIdNumberHash)
            '('QueueIdNumber queueIdNumber)
        )__";

const char* const DLQ_ID_KEYS = R"__(
            '('QueueIdNumberHash dlqIdNumberHash)
            '('QueueIdNumber dlqIdNumber)
        )__";

const char* const QUEUE_ID_AND_SHARD_KEYS = R"__(
            '('QueueIdNumberAndShardHash queueIdNumberAndShardHash)
            '('QueueIdNumber queueIdNumber)
            '('Shard shard)
        )__";

const char* const DLQ_ID_AND_SHARD_KEYS = R"__(
            '('QueueIdNumberAndShardHash dlqIdNumberAndShardHash)
            '('QueueIdNumber dlqIdNumber)
            '('Shard dlqShard)
        )__";

const char* const QUEUE_ID_AND_SHARD_KEYS_RANGE = R"__(
            '('QueueIdNumberAndShardHash queueIdNumberAndShardHash queueIdNumberAndShardHash)
            '('QueueIdNumber queueIdNumber queueIdNumber)
            '('Shard shard shard)
        )__";



class TDbQueriesMaker {
public:
    TDbQueriesMaker(
        const TString& root,
        const TString& userName,
        const TString& queueName,
        ui64 queueVersion,
        bool isFifo,
        ui64 shard,
        ui32 tablesFormat,
        const TString& dlqName,
        ui64 dlqShard,
        ui64 dlqVersion,
        ui32 dlqTablesFormat
    )
        : Root_(root)
        , QueueName_(queueName)
        , TablesFormat_(tablesFormat)
        , IsFifo_(isFifo)
        , DlqTablesFormat_(dlqTablesFormat)
    {
        FillQueueVars(
            userName, queueName, queueVersion, tablesFormat, shard,
            QueueTablesFolder_, QueueTablesFolderPerShard_
        );
        FillQueueVars(
            userName, dlqName, dlqVersion, dlqTablesFormat, dlqShard,
            DlqTablesFolder_, DlqTablesFolderPerShard_
        );
    }

    TString operator() (EQueryId id) {
        TString result = Sprintf(
            GetQueryById(id),
            Root_.c_str(),                          // 1
            QueueTablesFolderPerShard_.c_str(),     // 2
            QueueTablesFolder_.c_str(),             // 3

            QueueName_.c_str(),                     // 4
            GetIdKeys(),                            // 5
            GetIdKeysRange(),                       // 6
            GetIdAndShardKeys(),                    // 7
            GetIdAndShardKeysRange(),               // 8
            GetShardColumnType(TablesFormat_),      // 9
            GetShardColumnName(),                   // 10
            GetStateKeys(),                         // 11
            GetAttrKeys(),                          // 12
            GetAllShardsRange(),                    // 13

            DlqTablesFolder_.c_str(),               // 14
            DlqTablesFolderPerShard_.c_str(),       // 15

            GetDlqIdKeys(),                         // 16
            GetDlqIdAndShardKeys(),                 // 17
            GetShardColumnType(DlqTablesFormat_),   // 18
            GetDlqStateKeys()                       // 19
        );
        return result;
    }

    const char* GetStateKeys() const {
        if (TablesFormat_ == 0) {
            return IsFifo_ ? "'('State (Uint64 '0))" : "'('State shard)";
        }
        return IsFifo_ ? GetIdKeys() : GetIdAndShardKeys();
    }

    const char* GetDlqStateKeys() const {
        if (TablesFormat_ == 0) {
            return IsFifo_ ? "'('State (Uint64 '0))" : "'('State dlqShard)";
        }
        return IsFifo_ ? GetDlqIdKeys() : GetDlqIdAndShardKeys();
    }

    const char* GetAllShardsRange() const {
        if (TablesFormat_ == 1) {
            return "'('QueueIdNumber queueIdNumber queueIdNumber)";
        }
        return "'('State (Uint64 '0) (Uint64 '18446744073709551615))";
    }
    const char* GetAttrKeys() const {
        return TablesFormat_ == 1 ? QUEUE_ID_KEYS : "'('State (Uint64 '0))";
    }
    const char* GetIdKeys() const {
        return TablesFormat_ == 1 ? QUEUE_ID_KEYS : "";
    }
    const char* GetDlqIdKeys() const {
        return DlqTablesFormat_ == 1 ? DLQ_ID_KEYS : "";
    }
    const char* GetIdKeysRange() const {
        return TablesFormat_ == 1 ? QUEUE_ID_KEYS_RANGE : "";
    }
    const char* GetIdAndShardKeysRange() const {
        return TablesFormat_ == 1 ? QUEUE_ID_AND_SHARD_KEYS_RANGE : "";
    }
    const char* GetIdAndShardKeys() const {
        return TablesFormat_ == 1 ? QUEUE_ID_AND_SHARD_KEYS : "";
    }
    const char* GetDlqIdAndShardKeys() const {
        return TablesFormat_ == 1 ? DLQ_ID_AND_SHARD_KEYS : "";
    }
    const char* GetShardColumnName() const {
        return TablesFormat_ == 1 ? "Shard" : "State";
    }
    const char* GetShardColumnType(bool tablesFormat) const {
        return tablesFormat == 1 ? "Uint32" : "Uint64";
    }

    void FillQueueVars(
        const TString& userName,
        const TString& queueName,
        ui64 queueVersion,
        ui32 tablesFormat,
        ui64 shard,
        TString& tablesFolder,
        TString& tablesFolderPerShard
    ) {
        if (tablesFormat == 1) {
            tablesFolder = tablesFolderPerShard = TStringBuilder() << Root_ << "/" << (IsFifo_ ? ".FIFO" : ".STD");
        } else {
            TQueuePath path(Root_, userName, queueName, queueVersion);
            tablesFolder = path.GetVersionedQueuePath();
            tablesFolderPerShard = TStringBuilder() << tablesFolder << "/" << shard;
        }
    }

private:
    const char* GetQueryById(EQueryId id) {
        const char* query = IsFifo_ ? GetFifoQueryById(id) : GetStdQueryById(id);
        Y_VERIFY(query);
        return query;
    }

private:
    TString Root_;
    TString QueueTablesFolder_;
    TString QueueTablesFolderPerShard_;
    TString QueueName_;
    ui32 TablesFormat_;
    bool IsFifo_;
    TString DlqTablesFolder_;
    TString DlqTablesFolderPerShard_;
    ui32 DlqTablesFormat_;
};

} // namespace NKikimr::NSQS
