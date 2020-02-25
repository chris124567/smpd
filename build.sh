#!/bin/sh
set -euf
# CC="musl-gcc"
CC="gcc"
SOURCE="smpd"
FILES='main.c log.c util.c queue.c player.c status.c song.c search.c misc.c'

LINK="$(pkg-config --libs --cflags libmpdclient)"

# STATIC="-static -static-libgcc"
STATIC=""

# DEBUG="-DDEBUG"
DEBUG=""

# optimizations not supported with non-gcc compilers
if [ "$CC" = "gcc" ]
then
    GCC_OPT="-fipa-pta -fgraphite-identity -floop-nest-optimize -floop-parallelize-all -ftree-loop-if-convert -ftree-loop-distribution -floop-interchange -ftree-loop-im -ftree-loop-ivcanon -fivopts -fuse-linker-plugin -flto"
else
    GCC_OPT=""
fi

# only enable security features in debug builds, they slow down the application
if [ "$DEBUG" = "-DDEBUG" ]
then
    SEC="${GCC_OPT} -fstack-protector-all -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -D_FORTIFY_SOURCE=2 -fPIE -pie"
else
    SEC=""
fi

CFLAGS="-DLOG_USE_COLOR -ansi -pedantic -std=c99 -Wall -Wextra -Wshadow -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Ofast -march=native -ffast-math -fno-math-errno -ffinite-math-only -fno-signed-zeros -fmerge-all-constants -ftree-vectorize -s -Wl,--no-export-dynamic -Wl,--no-omagic -Wl,--strip-all -Wl,--discard-all -Wl,-z,defs -Wl,-z,nodelete -Wl,-z,nodump -Wl,-z,nodlopen -Wl,--no-demangle -Wl,--gc-sections -Wl,--disable-new-dtags -Wl,--hash-style=sysv -Wl,--build-id=none"
# CFLAGS=""

${CC} ${FILES} ${STATIC} ${LINK} ${GCC_OPT} ${SEC} ${CFLAGS} -o ${SOURCE} ${DEBUG}
