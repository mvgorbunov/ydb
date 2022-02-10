UNITTEST_FOR(ydb/services/persqueue_v1)

OWNER( 
    zhenyok 
    g:kikimr
    g:logbroker
) 
 
CFLAGS(
    -DACTORLIB_HUGE_PB_SIZE
)
 
FORK_SUBTESTS() 

IF (WITH_VALGRIND) 
    TIMEOUT(1800) 
    SIZE(LARGE) 
    TAG(ya:fat) 
    REQUIREMENTS(ram:32)
ELSE() 
    TIMEOUT(600) 
    SIZE(MEDIUM) 
ENDIF() 
 
ENV(PERSQUEUE_NEW_SCHEMECACHE="true") 
 
SRCS( 
    persqueue_new_schemecache_ut.cpp 
    persqueue_common_ut.cpp 
    ut/api_test_setup.h 
    ut/test_utils.h 
    ut/pq_data_writer.h 
    ut/rate_limiter_test_setup.h 
    ut/rate_limiter_test_setup.cpp 
) 
 
PEERDIR( 
    library/cpp/getopt
    library/cpp/svnversion
    ydb/core/testlib
    ydb/public/api/grpc
    ydb/public/sdk/cpp/client/resources
    ydb/public/sdk/cpp/client/ydb_persqueue_core/ut/ut_utils
    ydb/public/sdk/cpp/client/ydb_table
    ydb/services/persqueue_v1
) 
 
YQL_LAST_ABI_VERSION() 
 
END() 
