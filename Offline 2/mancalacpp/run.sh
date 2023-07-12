#!/usr/bin/bash

# g++ -std=c++17 1905118.cpp -o 1905118
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118
./1905118
