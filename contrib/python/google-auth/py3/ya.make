# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(2.30.0)

LICENSE(Apache-2.0)

PEERDIR(
    contrib/python/cachetools
    contrib/python/cryptography
    contrib/python/grpcio
    contrib/python/packaging
    contrib/python/pyasn1-modules
    contrib/python/requests
    contrib/python/rsa
)

NO_LINT()

NO_CHECK_IMPORTS(
    google.auth._oauth2client
    google.auth.transport._aiohttp_requests
)

PY_SRCS(
    TOP_LEVEL
    google/auth/__init__.py
    google/auth/_cloud_sdk.py
    google/auth/_credentials_async.py
    google/auth/_default.py
    google/auth/_default_async.py
    google/auth/_exponential_backoff.py
    google/auth/_helpers.py
    google/auth/_jwt_async.py
    google/auth/_oauth2client.py
    google/auth/_refresh_worker.py
    google/auth/_service_account_info.py
    google/auth/api_key.py
    google/auth/app_engine.py
    google/auth/aws.py
    google/auth/compute_engine/__init__.py
    google/auth/compute_engine/_metadata.py
    google/auth/compute_engine/credentials.py
    google/auth/credentials.py
    google/auth/crypt/__init__.py
    google/auth/crypt/_cryptography_rsa.py
    google/auth/crypt/_helpers.py
    google/auth/crypt/_python_rsa.py
    google/auth/crypt/base.py
    google/auth/crypt/es256.py
    google/auth/crypt/rsa.py
    google/auth/downscoped.py
    google/auth/environment_vars.py
    google/auth/exceptions.py
    google/auth/external_account.py
    google/auth/external_account_authorized_user.py
    google/auth/iam.py
    google/auth/identity_pool.py
    google/auth/impersonated_credentials.py
    google/auth/jwt.py
    google/auth/metrics.py
    google/auth/pluggable.py
    google/auth/transport/__init__.py
    google/auth/transport/_aiohttp_requests.py
    google/auth/transport/_custom_tls_signer.py
    google/auth/transport/_http_client.py
    google/auth/transport/_mtls_helper.py
    google/auth/transport/grpc.py
    google/auth/transport/mtls.py
    google/auth/transport/requests.py
    google/auth/transport/urllib3.py
    google/auth/version.py
    google/oauth2/__init__.py
    google/oauth2/_client.py
    google/oauth2/_client_async.py
    google/oauth2/_credentials_async.py
    google/oauth2/_id_token_async.py
    google/oauth2/_reauth_async.py
    google/oauth2/_service_account_async.py
    google/oauth2/challenges.py
    google/oauth2/credentials.py
    google/oauth2/gdch_credentials.py
    google/oauth2/id_token.py
    google/oauth2/reauth.py
    google/oauth2/service_account.py
    google/oauth2/sts.py
    google/oauth2/utils.py
    google/oauth2/webauthn_handler.py
    google/oauth2/webauthn_handler_factory.py
    google/oauth2/webauthn_types.py
)

RESOURCE_FILES(
    PREFIX contrib/python/google-auth/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
    google/auth/py.typed
    google/oauth2/py.typed
)

END()

RECURSE_FOR_TESTS(
    tests
)
