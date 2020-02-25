#!/bin/sh
set -euf
# CC="musl-gcc"
CC="gcc"
SOURCE="smpd"
FILES='main.c log.c util.c queue.c player.c status.c song.c search.c misc.c'

LINK="$(pkg-config --libs --cflags libmpdclient)"

# STATIC="-static -static-libgcc"
STATIC=""

DEBUG="-DDEBUG"
# DEBUG=""

GCC_OPT="-fipa-pta -fgraphite-identity -floop-nest-optimize -floop-parallelize-all -ftree-loop-if-convert -ftree-loop-distribution -floop-interchange -ftree-loop-im -ftree-loop-ivcanon -fivopts -fstack-clash-protection -fuse-linker-plugin -flto"
# GCC_OPT=""

CFLAGS="-DLOG_USE_COLOR -ansi -pedantic -std=c99 -Wall -Wextra -Wshadow -Wno-pointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Ofast -march=native -ffast-math -fno-math-errno -ffinite-math-only -fno-signed-zeros -fmerge-all-constants -ftree-vectorize -s -Wl,--no-export-dynamic -Wl,--no-omagic -Wl,--strip-all -Wl,--discard-all -Wl,-z,defs -Wl,-z,nodelete -Wl,-z,nodump -Wl,-z,nodlopen -Wl,--no-demangle -Wl,--gc-sections -Wl,--disable-new-dtags -Wl,--hash-style=sysv -Wl,--build-id=none -fstack-protector-all -Wl,-z,relro -Wl,-z,noexecstack"
# CFLAGS=""

${CC} ${FILES} ${STATIC} ${LINK} ${GCC_OPT} ${CFLAGS} -o ${SOURCE} ${DEBUG}
