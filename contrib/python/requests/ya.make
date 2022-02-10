# Generated by devtools/yamaker (pypi).

PY23_LIBRARY() 

OWNER(g:python-contrib)

VERSION(2.27.1)

LICENSE(Apache-2.0)

PEERDIR(
    contrib/python/certifi
    contrib/python/idna
    contrib/python/urllib3
)

IF (PYTHON2)
    PEERDIR(
        contrib/python/chardet
    )
ELSE()
    PEERDIR(
        contrib/python/charset-normalizer
    )
ENDIF()

NO_LINT()

PY_SRCS(
    TOP_LEVEL
    requests/__init__.py
    requests/__version__.py
    requests/_internal_utils.py
    requests/adapters.py
    requests/api.py
    requests/auth.py
    requests/certs.py
    requests/compat.py
    requests/cookies.py
    requests/exceptions.py
    requests/help.py
    requests/hooks.py
    requests/models.py
    requests/packages.py
    requests/sessions.py
    requests/status_codes.py
    requests/structures.py
    requests/utils.py
)

RESOURCE_FILES(
    PREFIX contrib/python/requests/
    .dist-info/METADATA
    .dist-info/top_level.txt
)

END()
