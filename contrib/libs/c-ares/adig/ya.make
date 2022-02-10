# Generated by devtools/yamaker. 
 
PROGRAM(adig) 
 
OWNER(max42 g:cpp-contrib)
 
LICENSE(MIT) 
 
PEERDIR( 
    contrib/libs/c-ares 
) 
 
ADDINCL( 
    contrib/libs/c-ares 
) 
 
NO_COMPILER_WARNINGS() 
 
CFLAGS(
    -DHAVE_CONFIG_H
)

SRCDIR(contrib/libs/c-ares) 
 
IF (NOT DLL_FOR) 
    CFLAGS( 
        -DCARES_STATICLIB 
    ) 
ENDIF() 
 
SRCS( 
    adig.c 
) 
 
END() 
