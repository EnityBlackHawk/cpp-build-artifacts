#!/bin/bash

# Limpar
rm app app.debug output.map

# Buildar
g++ -g1 -ffile-prefix-map=$PWD=. -fno-record-gcc-switches -fno-eliminate-unused-debug-types -O0 main.cpp -Xlinker -Map=output.map -o app

# Separar o debug simbol
objcopy --only-keep-debug app app.debug
strip --strip-debug --strip-unneeded app -o app