#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address 1905118gg.cpp -o 1905118gg
# g++ -std=c++17 -g 1905118.cpp -o 1905118
for i in $(seq 1 1 54)
do
    echo $i $(./1905118gg < ../set1/g$i.rud)
done
# gnome-terminal -- bash -c "./run1.sh; exec bash"
# gnome-terminal -- bash -c "./run2.sh; exec bash"
# gnome-terminal -- bash -c "./run3.sh; exec bash"
# gnome-terminal -- bash -c "./run4.sh; exec bash"
