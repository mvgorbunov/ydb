OWNER(
    g:contrib
    g:cpp-contrib
)

RECURSE(
    afl
    antlr4_cpp_runtime
    apache
    apr
    apr-util
    asio
    asmlib
    authparser
    avs-device-sdk
    aws-sdk-cpp
    backtrace
    base64
    bdb
    bdb/ut
    benchmark
    bento4
    bluez-clean-headers
    breakpad
    brotli
    c-ares 
    cairo
    cbc
    cctools
    cctz
    cereal
    ceres-solver
    chromaprint
    clang12
    clang12-rt
    clapack
    cld2
    cnpy
    cookiemy
    coreml
    coturn
    courgette_bsdiff
    cppkafka
    crcutil
    crfsuite
    croaring
    ctemplate
    curl
    cxxsupp/libcxx
    cxxsupp/libcxxabi-parts
    djvulibre
    dlib
    dpdk
    dr_wav
    dwarflib
    earcut
    eccodes
    eccodes/python
    eccodes/tools
    eigen
    expat
    falconn
    farmhash
    farmhash/ut
    faster-rnnlm
    fastlz
    fastops
    fcgi
    ffmpeg-3
    ffmpeg-3.4.1
    fft
    flatbuffers
    flatbuffers64
    flatbuffers64/flatc
    flatbuffers64/samples
    fmath
    fmt
    fontconfig
    fp16
    freetype
    fuse
    fxdiv
    gamma_function_apache_math_port
    gdal
    gdal/apps
    gdk-pixbuf
    geos
    geos/capi/ctypes
    gflags
    giflib
    glslang
    google-compute-engine-oslogin
    googleapis-common-protos
    gost-engine
    gpsd
    grpc
    grpc/python
    grpc/src/proto
    gtfs_realtime
    h3
    harfbuzz
    hdf5
    hdr_histogram
    highwayhash
    hiredis
    httpd24
    hwloc
    hyperscan
    i18n
    i18n/ut
    icu
    ImageMagick
    inja
    inja/ut
    intel
    isa-l
    isa-l/ut
    jansson
    jdk
    jemalloc
    jemalloc/dynamic
    jerasure
    jinja2cpp
    js-v8
    json-c
    jwt-cpp
    kaldi
    kenlm
    kissfft
    kyotocabinet
    lang_detect
    lbfgs
    lcms2
    lepton
    leveldb
    libarchive
    libbpf
    libbz2
    libc_compat
    libc_userver_workarounds
    libcpuid
    libcroco
    libde265
    libdivide
    libdivsufsort2
    libeatmydata/dynamic
    libev
    libevent
    libexslt
    libfdk-aac
    libfuzzer12
    libgeotiff
    libgit2
    libgraphqlparser
    libheif
    libical
    libiconv
    libidn
    libidn2
    libjpeg-turbo
    libjwt
    liblinear
    libm
    libmagic
    libmemcached
    libmp3lame
    libmysql_r
    libogg
    libopendkim
    libopendmarc
    libosmium
    libphonenumber
    libpng
    libpq
    libpqxx
    libpsl
    libraw
    librdkafka
    librosa-cpp
    librsvg
    libsamplerate
    libsavi
    libsodium
    libspf2
    libsrtp
    libssh2
    libtapi
    libtess2
    libtiff
    libunistring
    libunwind
    liburing
    libuv
    libvorbis
    libvorbis/libvorbisenc
    libvpx
    libwebp
    libx264
    libx265
    libxml
    libxml/dynamic
    libxslt
    libyang
    libyuv
    linenoise
    linux-headers
    linuxvdso
    liquidfun
    llvm11
    llvm12
    llvm8
    lmdbxx
    lmdbxx/check
    lmdbxx/example
    lua
    lua-cjson
    luajit_21
    lz4
    lz4/generated
    lzmasdk
    lzo2
    matrixssl
    mecab
    metrohash
    mimalloc
    minilzo
    minizip
    mlir11
    mms
    mongo-c-driver
    mongo-cxx-driver
    msgpack
    muparser
    muparser/tests
    musl
    nanosvg
    nanosvg/ut
    nayuki_md5
    nghttp2
    node-addon-api
    nodejs_12
    node_nan
    nsync
    numa
    nvidia
    odpi
    onnx
    opencl-headers
    opencv
    opencv/modules
    opencv/modules/python/src2
    openfst
    opengv
    openjpeg
    openldap
    openldap/libraries
    openmp
    openssl
    opentracing-cpp
    opus
    ortools
    ortools/proto
    osrm
    pam
    pango
    pcre
    pcre2
    pdqsort
    pffft
    pfr
    picohttpparser
    #pire/ut
    pixman
    poco
    portaudio
    porto_api
    proj
    protobuf
    protobuf/python
    protobuf-mutator
    protobuf_std
    protoc_std
    psimd
    pthreadpool
    pugixml
    pybind11
    pycxx
    python
    python/ut
    qhull
    quicklz
    r-lang
    re2
    regional-units/library
    regional-units/library/ut
    rocksdb
    rocksdb/tools/ldb
    rocksdb/tools/sst_dump
    sasl
    sctp
    sentencepiece
    serf
    snappy
    sophos
    sparrowhawk
    sparsehash
    spdk
    speex
    spirv_cross
    spirv_headers
    spirv_tools
    sqlite3
    srt
    stan
    stan-math
    stan/stan/command
    stxxl
    subversion
    sundials
    svm
    svt-hevc
    svt-vp9
    szip
    t1ha
    taocrypt
    tbb
    tcmalloc
    tcmalloc/dynamic
    tensorboard
    termbox
    tf
    tf/samples
    tf/tensorflow
    tf/tensorflow/compiler
    tf/tests
    tf-2.4
    tf-2.4/sample_python
    tf-2.4/tensorflow/python
    thrax
    tinyalsa
    tlsh
    trace_viewer
    tralics
    tree_sitter
    uatraits
    usrsctp
    utf8proc
    util-linux
    valgrind
    vlfeat
    vmaf
    wapiti
    webrtc
    websocketpp
    woff2
    xdelta3
    xmlsec
    xpdf-3.04
    xxhash
    xz
    yajl
    yaml
    yaml-cpp
    zeromq
    zlib
    zlib-ng-develop
    zookeeper
    zstd
    zstd06
    zzip
)

IF (OS_FREEBSD OR OS_LINUX)
    RECURSE(
        asmglibc
        httpd
        mod_perl2
        libeatmydata
    )
ENDIF()

IF (OS_DARWIN)
    RECURSE(
        gperftools
        osxfuse
        macfuse-headers
        uuid
    )
ENDIF()

IF (OS_LINUX)
    RECURSE(
        ibdrv
        ibdrv/ut
        proc
        luajit
        luajit_21
        libaio
        libcap
        libmnl
        libnfnetlink
        libnetfilter_log
        libnetfilter_conntrack
        openmpi
        sdbus-cpp
        systemd
        uuid
        virtiofsd
    )
ENDIF()

IF (OS_WINDOWS)
    RECURSE(
        pthreads_win32
        dokany/dokan
        dokany/dokan_fuse
    )
ELSE()
    RECURSE(
        lftp
        unixodbc
    )
ENDIF()

IF (OS_LINUX OR OS_WINDOWS)
    RECURSE(
        lockless
    )
ENDIF()

IF (OS_ANDROID)
    RECURSE(
        android_cpufeatures
        android_crazy_linker
    )
ENDIF()

IF (OS_IOS AND ARCH_ARM64 OR OS_DARWIN)
    RECURSE(
        MoltenVK
    )
ENDIF()

IF (MUSL)
    RECURSE(musl_extra)
ENDIF()
