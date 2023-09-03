#! /usr/bin/bash
clear
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118.o
# g++ -g -std=c++17 1905118.cpp -o 1905118.o
./1905118.o 20 0.8

# rm graph.dat
# for i in $(seq 0.01 0.01 0.99)
# do
#     ./1905118.o 20 $i >> graph.dat
# done

# gnuplot -c "plot_graph.sh" "graph.png" "graph.dat"