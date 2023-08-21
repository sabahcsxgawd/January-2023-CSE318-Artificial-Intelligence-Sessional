#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118
# gnome-terminal -- bash -c "./test.o 35 < ../set1/g35.rud > output/out.txt; exec bash"
# rm test.o
./1905118 1 < ../set1/g35.rud