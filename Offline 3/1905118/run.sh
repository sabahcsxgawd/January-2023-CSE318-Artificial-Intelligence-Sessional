#!/usr/bin/bash
g++ -std=c++17 -fsanitize=address 1905118.cpp -o 1905118
# g++ -std=c++17 -g 1905118.cpp -o 1905118
# ./1905118 < ../set1/g1.rud > ./output/out1.txt
# for i in $(seq 1 1 54)
# do
    # time ./1905118 < ../set1/g$i.rud > ./output/out$i.txt
    # echo $i
    # time ./1905118 < ../set1/g$i.rud
    # echo $i $(head -n 1 ../set1/g$i.rud)
# done
gnome-terminal -- bash -c "./1905118 1 < ../set1/g1.rud > output/out1.txt; exec bash"
gnome-terminal -- bash -c "./1905118 11 < ../set1/g11.rud > output/out11.txt; exec bash"
gnome-terminal -- bash -c "./1905118 14 < ../set1/g14.rud > output/out14.txt; exec bash"
gnome-terminal -- bash -c "./1905118 22 < ../set1/g22.rud > output/out22.txt; exec bash"
gnome-terminal -- bash -c "./1905118 32 < ../set1/g32.rud > output/out32.txt; exec bash"
gnome-terminal -- bash -c "./1905118 37 < ../set1/g37.rud > output/out37.txt; exec bash"
gnome-terminal -- bash -c "./1905118 45 < ../set1/g45.rud > output/out45.txt; exec bash"
gnome-terminal -- bash -c "./1905118 49 < ../set1/g49.rud > output/out49.txt; exec bash"
# gnome-terminal --title="g22" -- bash -c "time ./1905118 < ../set1/g22.rud; exec bash"
# gnome-terminal --title="g32" -- bash -c "time ./1905118 < ../set1/g32.rud; exec bash"
# gnome-terminal --title="g35" -- bash -c "time ./1905118 < ../set1/g35.rud; exec bash"
# ./1905118 1 < ../set1/g1.rud > output/out1.csv
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g22.rud
# time ./1905118 < ../set1/g48.rud
# time ./1905118 < ../set1/g49.rud
# time ./1905118 < ../set1/g25.rud
# ./1905118 < in.txt
