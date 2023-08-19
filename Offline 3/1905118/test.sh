#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address test.cpp -o test.o
# gnome-terminal -- bash -c "./test.o 35 < ../set1/g35.rud > output/out.txt; exec bash"
# rm test.o