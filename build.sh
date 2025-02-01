#!/usr/bin/env bash

rm -rf build/*

gcc -c src/lexer.c -Iinclude -o build/lexer.o
gcc -c src/scanner.c -Iinclude -o build/scanner.o
gcc -c src/main.c -Iinclude -o build/main.o

gcc build/main.o build/scanner.o build/lexer.o -o build/cmc
