#!/usr/bin/bash

set -xeuf -o pipefail

# adapted from https://github.com/google/fuzzer-test-suite/blob/master/common.sh

CC="clang"
CFLAGS="-O2 -fno-omit-frame-pointer -g -fsanitize=address,fuzzer -fsanitize-address-use-after-scope -I../arithmetic-expressions-calc/"
CPPFLAGS=""

$CC $CPPFLAGS $CFLAGS -o target target.c
