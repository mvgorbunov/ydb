#pragma once

#include "topic_workload_stats_collector.h"

#include <ydb/public/lib/ydb_cli/commands/ydb_workload.h>

#include <library/cpp/logger/log.h>

namespace NYdb {
    namespace NConsoleClient {
        class TCommandWorkloadTopicRunRead: public TWorkloadCommand {
        public:
            TCommandWorkloadTopicRunRead();
            virtual void Config(TConfig& config) override;
            virtual void Parse(TConfig& config) override;
            virtual int Run(TConfig& config) override;

        private:
            size_t Seconds;

            ui32 ConsumerThreadCount;
            ui32 ConsumerCount;

            std::shared_ptr<TLog> Log;

            std::shared_ptr<std::atomic_bool> ErrorFlag;

            std::shared_ptr<TTopicWorkloadStatsCollector> StatsCollector;
        };
    }
}
