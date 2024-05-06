# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(3.11.3)

LICENSE(Apache-2.0)

PEERDIR(
    contrib/python/aiohttp
    contrib/python/grpcio
    contrib/python/packaging
    contrib/python/protobuf
)

NO_LINT()

NO_CHECK_IMPORTS(
    ydb.public.api.grpc
    ydb.public.api.grpc.*
)

PY_SRCS(
    TOP_LEVEL
    ydb/__init__.py
    ydb/_apis.py
    ydb/_errors.py
    ydb/_grpc/__init__.py
    ydb/_grpc/common/__init__.py
    ydb/_grpc/grpcwrapper/__init__.py
    ydb/_grpc/grpcwrapper/common_utils.py
    ydb/_grpc/grpcwrapper/ydb_scheme.py
    ydb/_grpc/grpcwrapper/ydb_topic.py
    ydb/_grpc/grpcwrapper/ydb_topic_public_types.py
    ydb/_session_impl.py
    ydb/_sp_impl.py
    ydb/_topic_common/__init__.py
    ydb/_topic_common/common.py
    ydb/_topic_reader/__init__.py
    ydb/_topic_reader/datatypes.py
    ydb/_topic_reader/topic_reader.py
    ydb/_topic_reader/topic_reader_asyncio.py
    ydb/_topic_reader/topic_reader_sync.py
    ydb/_topic_writer/__init__.py
    ydb/_topic_writer/topic_writer.py
    ydb/_topic_writer/topic_writer_asyncio.py
    ydb/_topic_writer/topic_writer_sync.py
    ydb/_tx_ctx_impl.py
    ydb/_utilities.py
    ydb/aio/__init__.py
    ydb/aio/_utilities.py
    ydb/aio/connection.py
    ydb/aio/credentials.py
    ydb/aio/driver.py
    ydb/aio/iam.py
    ydb/aio/oauth2_token_exchange.py
    ydb/aio/pool.py
    ydb/aio/resolver.py
    ydb/aio/scheme.py
    ydb/aio/table.py
    ydb/auth_helpers.py
    ydb/connection.py
    ydb/convert.py
    ydb/credentials.py
    ydb/dbapi/__init__.py
    ydb/dbapi/connection.py
    ydb/dbapi/cursor.py
    ydb/dbapi/errors.py
    ydb/default_pem.py
    ydb/draft/__init__.py
    ydb/draft/dynamic_config.py
    ydb/driver.py
    ydb/export.py
    ydb/global_settings.py
    ydb/iam/__init__.py
    ydb/iam/auth.py
    ydb/import_client.py
    ydb/interceptor.py
    ydb/issues.py
    ydb/oauth2_token_exchange/__init__.py
    ydb/oauth2_token_exchange/token_exchange.py
    ydb/oauth2_token_exchange/token_source.py
    ydb/operation.py
    ydb/pool.py
    ydb/resolver.py
    ydb/scheme.py
    ydb/scripting.py
    ydb/settings.py
    ydb/sqlalchemy/__init__.py
    ydb/sqlalchemy/types.py
    ydb/table.py
    ydb/topic.py
    ydb/tracing.py
    ydb/types.py
    ydb/ydb_version.py
)

RESOURCE_FILES(
    PREFIX contrib/python/ydb/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
)

END()
