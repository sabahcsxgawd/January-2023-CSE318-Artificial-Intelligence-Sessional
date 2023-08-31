#! /usr/bin/bash
clear
g++ -std=c++17 -fsanitize=address test.cpp -o test.o
# g++ -std=c++17 1905118.cpp -o 1905118.o
./test.o