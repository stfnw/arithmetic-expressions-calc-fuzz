Here we add instrumentation using [libFuzzer](https://llvm.org/docs/LibFuzzer.html) together with AddressSanitizer.
The program needs to be recompiled for that.

The following commands will build the calculator with libFuzzer.
Running `target` will feed fuzz data into each evaluation method while asserting that all methods return the same result.

```
$ git clone --recurse-submodules https://github.com/stfnw/arithmetic-expressions-calc-fuzz
$ cd libfuzzer

$ ./build.sh
+ CC=clang
+ CFLAGS='-O2 -fno-omit-frame-pointer -g -fsanitize=address,fuzzer -fsanitize-address-use-after-scope -I../arithmetic-expressions-calc/'
+ CPPFLAGS=
+ clang -O2 -fno-omit-frame-pointer -g -fsanitize=address,fuzzer -fsanitize-address-use-after-scope -I../arithmetic-expressions-calc/ -o target target.c

$ ./target
```

# Identified bugs

TODO
