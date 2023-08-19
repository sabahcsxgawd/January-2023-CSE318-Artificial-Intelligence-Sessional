#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address test.cpp -o test.o
./test.o
rm test.o