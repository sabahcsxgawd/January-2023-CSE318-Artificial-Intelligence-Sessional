#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118
# g++ -std=c++17 -g 1905118.cpp -o 1905118
# ./1905118 < ../set1/g1.rud > ./output/out1.txt
# for i in $(seq 1 1 54)
# do
    # ./1905118 < ../set1/g$i.rud > ./output/out$i.txt
# done
./1905118 < ../set1/g12.rud
# ./1905118 < in.txt