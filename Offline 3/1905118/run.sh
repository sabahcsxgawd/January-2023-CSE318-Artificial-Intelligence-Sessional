#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118
# g++ -std=c++17 -g 1905118.cpp -o 1905118
# ./1905118 < ../set1/g1.rud > ./output/out1.txt
for i in $(seq 1 1 54)
do
    # time ./1905118 < ../set1/g$i.rud > ./output/out$i.txt
    # echo $i
    # time ./1905118 < ../set1/g$i.rud
    echo $i $(head -n 1 ../set1/g$i.rud)
done
# gnome-terminal --title="g1" -- bash -c "time ./1905118 < ../set1/g1.rud; exec bash"
# gnome-terminal --title="g11" -- bash -c "time ./1905118 < ../set1/g11.rud; exec bash"
# gnome-terminal --title="g14" -- bash -c "time ./1905118 < ../set1/g14.rud; exec bash"
# gnome-terminal --title="g22" -- bash -c "time ./1905118 < ../set1/g22.rud; exec bash"
# gnome-terminal --title="g32" -- bash -c "time ./1905118 < ../set1/g32.rud; exec bash"
# gnome-terminal --title="g35" -- bash -c "time ./1905118 < ../set1/g35.rud; exec bash"
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g48.rud
# time ./1905118 < ../set1/g49.rud
# time ./1905118 < ../set1/g25.rud
# ./1905118 < in.txt
