LIBRARY()

PEERDIR(
    ydb/library/yql/core/issue/protos
    ydb/library/yql/parser/proto_ast
    ydb/library/yql/parser/proto_ast/gen/v0
    ydb/library/yql/parser/proto_ast/antlr3
)

SRCS(
    lexer.cpp
)

END()
