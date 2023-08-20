#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118
# g++ -std=c++17 -g 1905118.cpp -o 1905118

gnome-terminal -- bash -c "./run1.sh; exec bash"
gnome-terminal -- bash -c "./run2.sh; exec bash"
gnome-terminal -- bash -c "./run3.sh; exec bash"
gnome-terminal -- bash -c "./run4.sh; exec bash"
