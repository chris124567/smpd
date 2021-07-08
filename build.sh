#!/bin/sh
set -eux
CC="gcc"
CFLAGS="-std=c99 -fdata-sections -ffunction-sections"
# CFLAGS="$CFLAGS -DDEBUG=1 -DLOG_USE_COLOR"
CFLAGS="$CFLAGS -Wall -Wextra -Wstrict-prototypes -pedantic -Wno-unused-parameter"
CFLAGS="$CFLAGS -s -Wl,--no-export-dynamic -Wl,--no-omagic -Wl,--discard-all -Wl,-z,defs -Wl,-z,nodelete -Wl,-z,nodump -Wl,-z,nodlopen -Wl,--no-demangle -Wl,--gc-sections -Wl,--as-needed -Wl,--relax -Wl,--disable-new-dtags -Wl,--hash-style=sysv -Wl,--build-id=none -Wl,--no-eh-frame-hdr -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,-z,noseparate-code"
CFLAGS="$CFLAGS -flto -Ofast -march=native -fmerge-all-constants"
CFLAGS="$CFLAGS $(pkg-config --libs --cflags libmpdclient)"
# CFLAGS="$CFLAGS -fsanitize=leak"
clang-format-11 -i -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 0}" *.c *.h
$CC *.c -o smpd $CFLAGS
