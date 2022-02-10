#include "yql_pq_provider_impl.h"
#include "yql_pq_helpers.h"

#include <ydb/library/yql/core/yql_expr_optimize.h>
#include <ydb/library/yql/utils/log/log.h>
#include <ydb/library/yql/providers/pq/expr_nodes/yql_pq_expr_nodes.h>

namespace NYql {

namespace {

using namespace NNodes;

class TPqDataSinkIODiscoveryTransformer : public TGraphTransformerBase {
using TDbId2Endpoint = THashMap<std::pair<TString, NYq::DatabaseType>, NYq::TEvents::TDbResolverResponse::TEndpoint>;
public:
    explicit TPqDataSinkIODiscoveryTransformer(TPqState::TPtr state)
        : State_(state)
    {
    }

    TStatus DoTransform(TExprNode::TPtr input, TExprNode::TPtr& output, TExprContext& ctx) final {
        Y_UNUSED(ctx);
        output = input;
        if (ctx.Step.IsDone(TExprStep::DiscoveryIO))
            return TStatus::Ok;

        if (!State_->DbResolver)
            return TStatus::Ok;

        THashMap<std::pair<TString, NYq::DatabaseType>, NYq::TEvents::TDatabaseAuth> ids;
        FindYdsDbIdsForResolving(State_, input, ids);

        if (ids.empty())
            return TStatus::Ok;

        const std::weak_ptr<NYq::TEvents::TDbResolverResponse> response = DbResolverResponse_;
        AsyncFuture_ = State_->DbResolver->ResolveIds({ids, State_->DbResolver->GetTraceId()}).Apply([response](auto future)
        {
            if (const auto res = response.lock())
                *res = std::move(future.ExtractValue());
        });
        return TStatus::Async;
    }

    NThreading::TFuture<void> DoGetAsyncFuture(const TExprNode&) final {
        return AsyncFuture_;
    }

    TStatus DoApplyAsyncChanges(TExprNode::TPtr input, TExprNode::TPtr& output, TExprContext& ctx) final {
        output = input;
        AsyncFuture_.GetValue();
        if (!DbResolverResponse_->Success) {
            ctx.IssueManager.AddIssues(DbResolverResponse_->Issues);
            return TStatus::Error;
        }
        FullResolvedIds_.insert(DbResolverResponse_->DatabaseId2Endpoint.begin(), DbResolverResponse_->DatabaseId2Endpoint.end());
        DbResolverResponse_ = std::make_shared<NYq::TEvents::TDbResolverResponse>();
        FillSettingsWithResolvedYdsIds(State_, FullResolvedIds_);
        return TStatus::Ok;
    }

private:
    const TPqState::TPtr State_;
    NThreading::TFuture<void> AsyncFuture_;
    TDbId2Endpoint FullResolvedIds_;
    std::shared_ptr<NYq::TEvents::TDbResolverResponse> DbResolverResponse_ = std::make_shared<NYq::TEvents::TDbResolverResponse>();
};
}

THolder<IGraphTransformer> CreatePqDataSinkIODiscoveryTransformer(TPqState::TPtr state) {
    return THolder(new TPqDataSinkIODiscoveryTransformer(state));
}

}
