# Generated by devtools/yamaker.

PROGRAM(python3)

VERSION(3.12.4)

ORIGINAL_SOURCE(https://github.com/python/cpython/archive/v3.12.4.tar.gz)

LICENSE(Python-2.0)

USE_PYTHON3()

PEERDIR(
    contrib/tools/python3/Modules/_sqlite
)

CFLAGS(
    -DPy_BUILD_CORE
)

SRCS(
    ../Programs/python.c
)

END()
