#!/bin/bash

# Limpar
mkdir build/
rm build/*

# Builar lib
g++ -g1 -ffile-prefix-map=$PWD=. -fno-record-gcc-switches -fno-eliminate-unused-debug-types -O3 -fPIC -shared -o build/libFoo.so lib.cpp

# Separar o debug simbol
objcopy --only-keep-debug build/libFoo.so build/libFoo.debug
strip --strip-debug --strip-unneeded build/libFoo.so -o build/libFoo.so

# Buildar bin
g++ -g1 -ffile-prefix-map=$PWD=. -fno-record-gcc-switches -fno-eliminate-unused-debug-types -O3 -Xlinker -Map=output.map -o build/app \
-Lbuild -lFoo -Wl,-rpath=build \
main.cpp

# Separar o debug simbol
objcopy --only-keep-debug build/app build/app.debug
strip --strip-debug --strip-unneeded build/app -o build/app

export ADDR_ARGS="-f -C -e"