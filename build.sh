#!/usr/bin/env bash

rm -rf build/*
mkdir -p build/src

gcc -c src/lexer.c -Iinclude -o build/lexer.o
gcc -c src/scanner.c -Iinclude -o build/scanner.o
bison -d src/parser.y -o build/src/parser.c
rm include/parser.h
mv build/src/parser.h include/parser.h
gcc -c build/src/parser.c -Iinclude -o build/parser.o
gcc -c src/main.c -Iinclude -o build/main.o

gcc build/main.o build/scanner.o build/lexer.o build/parser.o -o build/cmc
