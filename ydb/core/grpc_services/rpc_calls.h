#pragma once
#include "defs.h"

#include "local_rate_limiter.h"

#include <ydb/library/ydb_issue/issue_helpers.h>
#include <ydb/core/grpc_services/base/base.h>

#include <ydb/public/api/protos/ydb_auth.pb.h>
#include <ydb/public/api/protos/ydb_clickhouse_internal.pb.h>

#include <ydb/public/api/protos/ydb_coordination.pb.h>
#include <ydb/public/api/protos/ydb_discovery.pb.h>
#include <ydb/public/api/protos/ydb_monitoring.pb.h>
#include <ydb/public/api/protos/ydb_status_codes.pb.h>
#include <ydb/public/api/protos/ydb_table.pb.h>
#include <ydb/public/api/protos/ydb_persqueue_cluster_discovery.pb.h>
#include <ydb/public/api/protos/ydb_persqueue_v1.pb.h>
#include <ydb/public/api/protos/ydb_topic.pb.h>
#include <ydb/public/api/protos/ydb_federation_discovery.pb.h>

#include <ydb/public/api/grpc/draft/dummy.pb.h>

#include <ydb/public/lib/operation_id/operation_id.h>

#include <util/generic/maybe.h>

namespace NKikimr {
namespace NGRpcService {

template <>
void FillYdbStatus(Ydb::PersQueue::V1::StreamingWriteServerMessage& resp, const NYql::TIssues& issues, Ydb::StatusIds::StatusCode status);

template <>
void FillYdbStatus(Ydb::PersQueue::V1::MigrationStreamingReadServerMessage& resp, const NYql::TIssues& issues, Ydb::StatusIds::StatusCode status);

template <>
void FillYdbStatus(Ydb::Topic::StreamWriteMessage::FromServer& resp, const NYql::TIssues& issues, Ydb::StatusIds::StatusCode status);

template <>
void FillYdbStatus(Ydb::Topic::StreamReadMessage::FromServer& resp, const NYql::TIssues& issues, Ydb::StatusIds::StatusCode status);

template <>
void FillYdbStatus(Draft::Dummy::PingResponse& resp, const NYql::TIssues& issues, Ydb::StatusIds::StatusCode status);

template <>
void FillYdbStatus(Ydb::Coordination::SessionResponse& resp, const NYql::TIssues& issues, Ydb::StatusIds::StatusCode status);

inline bool ValidateAndReplyOnError(IRequestProxyCtx* ctx) {
    TString validationError;
    if (!ctx->Validate(validationError)) {
        const auto issue = MakeIssue(NKikimrIssues::TIssuesIds::YDB_API_VALIDATION_ERROR, validationError);
        ctx->RaiseIssue(issue);
        ctx->ReplyWithYdbStatus(Ydb::StatusIds::BAD_REQUEST);
        return false;
    } else {
        return true;
    }
}


using TEvListEndpointsRequest = TGRpcRequestWrapper<TRpcServices::EvListEndpoints, Ydb::Discovery::ListEndpointsRequest, Ydb::Discovery::ListEndpointsResponse, true>;

using TEvBiStreamPingRequest = TGRpcRequestBiStreamWrapper<TRpcServices::EvBiStreamPing, Draft::Dummy::PingRequest, Draft::Dummy::PingResponse>;
using TEvStreamPQWriteRequest = TGRpcRequestBiStreamWrapper<TRpcServices::EvStreamPQWrite, Ydb::PersQueue::V1::StreamingWriteClientMessage, Ydb::PersQueue::V1::StreamingWriteServerMessage>;
using TEvStreamPQMigrationReadRequest = TGRpcRequestBiStreamWrapper<TRpcServices::EvStreamPQMigrationRead, Ydb::PersQueue::V1::MigrationStreamingReadClientMessage, Ydb::PersQueue::V1::MigrationStreamingReadServerMessage>;
using TEvStreamTopicWriteRequest = TGRpcRequestBiStreamWrapper<TRpcServices::EvStreamTopicWrite, Ydb::Topic::StreamWriteMessage::FromClient, Ydb::Topic::StreamWriteMessage::FromServer, TRateLimiterMode::RuManual>;
using TEvStreamTopicReadRequest = TGRpcRequestBiStreamWrapper<TRpcServices::EvStreamTopicRead, Ydb::Topic::StreamReadMessage::FromClient, Ydb::Topic::StreamReadMessage::FromServer, TRateLimiterMode::RuManual>;
using TEvCommitOffsetRequest = TGRpcRequestWrapper<TRpcServices::EvTopicCommitOffset, Ydb::Topic::CommitOffsetRequest, Ydb::Topic::CommitOffsetResponse, true>;
using TEvPQReadInfoRequest = TGRpcRequestWrapper<TRpcServices::EvPQReadInfo, Ydb::PersQueue::V1::ReadInfoRequest, Ydb::PersQueue::V1::ReadInfoResponse, true>;
using TEvPQDropTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvPQDropTopic, Ydb::PersQueue::V1::DropTopicRequest, Ydb::PersQueue::V1::DropTopicResponse, true>;
using TEvPQCreateTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvPQCreateTopic, Ydb::PersQueue::V1::CreateTopicRequest, Ydb::PersQueue::V1::CreateTopicResponse, true>;
using TEvPQAlterTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvPQAlterTopic, Ydb::PersQueue::V1::AlterTopicRequest, Ydb::PersQueue::V1::AlterTopicResponse, true>;
using TEvPQDescribeTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvPQDescribeTopic, Ydb::PersQueue::V1::DescribeTopicRequest, Ydb::PersQueue::V1::DescribeTopicResponse, true>;
using TEvPQAddReadRuleRequest = TGRpcRequestValidationWrapper<TRpcServices::EvPQAddReadRule, Ydb::PersQueue::V1::AddReadRuleRequest, Ydb::PersQueue::V1::AddReadRuleResponse, true>;
using TEvPQRemoveReadRuleRequest = TGRpcRequestValidationWrapper<TRpcServices::EvPQRemoveReadRule, Ydb::PersQueue::V1::RemoveReadRuleRequest, Ydb::PersQueue::V1::RemoveReadRuleResponse, true>;

//TODO: Change this to runtime dispatching!
using TEvDropTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvDropTopic, Ydb::Topic::DropTopicRequest, Ydb::Topic::DropTopicResponse, true, TRateLimiterMode::Rps>;
using TEvCreateTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvCreateTopic, Ydb::Topic::CreateTopicRequest, Ydb::Topic::CreateTopicResponse, true, TRateLimiterMode::Rps>;
using TEvAlterTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvAlterTopic, Ydb::Topic::AlterTopicRequest, Ydb::Topic::AlterTopicResponse, true, TRateLimiterMode::Rps>;
using TEvDescribeTopicRequest = TGRpcRequestValidationWrapper<TRpcServices::EvDescribeTopic, Ydb::Topic::DescribeTopicRequest, Ydb::Topic::DescribeTopicResponse, true, TRateLimiterMode::Rps>;
using TEvDescribeConsumerRequest = TGRpcRequestValidationWrapper<TRpcServices::EvDescribeConsumer, Ydb::Topic::DescribeConsumerRequest, Ydb::Topic::DescribeConsumerResponse, true, TRateLimiterMode::Rps>;
using TEvDescribePartitionRequest = TGRpcRequestValidationWrapper<TRpcServices::EvDescribePartition, Ydb::Topic::DescribePartitionRequest, Ydb::Topic::DescribePartitionResponse, true, TRateLimiterMode::Rps>;

using TEvDiscoverPQClustersRequest = TGRpcRequestWrapper<TRpcServices::EvDiscoverPQClusters, Ydb::PersQueue::ClusterDiscovery::DiscoverClustersRequest, Ydb::PersQueue::ClusterDiscovery::DiscoverClustersResponse, true>;
using TEvListFederationDatabasesRequest = TGRpcRequestWrapper<TRpcServices::EvListFederationDatabases, Ydb::FederationDiscovery::ListFederationDatabasesRequest, Ydb::FederationDiscovery::ListFederationDatabasesResponse, true>;

using TEvLoginRequest = TGRpcRequestWrapperNoAuth<TRpcServices::EvLogin, Ydb::Auth::LoginRequest, Ydb::Auth::LoginResponse>;
using TEvNodeCheckRequest = TGRpcRequestWrapperNoAuth<TRpcServices::EvNodeCheckRequest, Ydb::Monitoring::NodeCheckRequest, Ydb::Monitoring::NodeCheckResponse>;
using TEvCoordinationSessionRequest = TGRpcRequestBiStreamWrapper<TRpcServices::EvCoordinationSession, Ydb::Coordination::SessionRequest, Ydb::Coordination::SessionResponse>;


// Stream{PQ,Topic}Read/Write specifics.
//
// Stream topic read/write operations use RefreshToken request to prolongate effect of
// established client auth state while working with a stream for a long time.
// As reads and writes require different permission sets (see TGrpcRequestCheckActor::GetPermissions()
// for implementation), RefreshToken also should specify different permission sets
// when refreshing tokens for the reads or for the writes.
//
// Essentially, there are two different RefreshToken rpc calls, both implemented by
// the TRefreshTokenImpl template class and selection between specializations is tailored to
// the C++ type of the stream request that initiates token refresh.

using TRefreshTokenGenericRequest = TRefreshTokenImpl<TRpcServices::EvRefreshToken>;
using TRefreshTokenStreamWriteSpecificRequest = TRefreshTokenImpl<TRpcServices::EvStreamWriteRefreshToken>;

template <typename TRequest>
struct TRefreshTokenTypeForRequest;
//NOTE: Intentionally left undefined to break compilation for any request type
// that does not have explicit specialization below.
// (Can't use static_assert here because then there won't be a problematic request type name in the error.)

template <>
struct TRefreshTokenTypeForRequest<TEvBiStreamPingRequest> {
    using type = TRefreshTokenGenericRequest;
};

template <>
struct TRefreshTokenTypeForRequest<TEvStreamPQMigrationReadRequest> {
    using type = TRefreshTokenGenericRequest;
};

template <>
struct TRefreshTokenTypeForRequest<TEvStreamTopicReadRequest> {
    using type = TRefreshTokenGenericRequest;
};

template <>
struct TRefreshTokenTypeForRequest<TEvStreamPQWriteRequest> {
    using type = TRefreshTokenStreamWriteSpecificRequest;
};

template <>
struct TRefreshTokenTypeForRequest<TEvStreamTopicWriteRequest> {
    using type = TRefreshTokenStreamWriteSpecificRequest;
};

// RefreshToken Send/Reply interface hides lowlevel details.
// Used to avoid unwanted compile time dependencies.
//
void RefreshTokenSendRequest(const TActorContext& ctx, IEventBase* refreshTokenRequest);
void RefreshTokenReplyUnauthenticated(TActorId recipient, TActorId sender, NYql::TIssues&& issues);
void RefreshTokenReplyUnavailable(TActorId recipient, NYql::TIssues&& issues);

template <ui32 TRpcId, typename TReq, typename TResp, TRateLimiterMode RlMode>
void TGRpcRequestBiStreamWrapper<TRpcId, TReq, TResp, RlMode>::RefreshToken(const TString& token, const TActorContext& ctx, TActorId id) {
    using TSelf = typename std::remove_pointer<decltype(this)>::type;
    using TRefreshToken = typename TRefreshTokenTypeForRequest<TSelf>::type;
    RefreshTokenSendRequest(ctx, new TRefreshToken(token, GetDatabaseName().GetOrElse(""), id));
}

template <ui32 TRpcId>
void TRefreshTokenImpl<TRpcId>::ReplyUnauthenticated(const TString&) {
    RefreshTokenReplyUnauthenticated(From_, TActorId(), IssueManager_.GetIssues());
}

template <ui32 TRpcId>
void TRefreshTokenImpl<TRpcId>::ReplyUnavaliable() {
    RefreshTokenReplyUnavailable(From_, IssueManager_.GetIssues());
}

} // namespace NGRpcService
} // namespace NKikimr
