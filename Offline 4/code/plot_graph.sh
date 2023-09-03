#!/usr/bin/gnuplot -persist
set terminal png
set terminal png size 1024,768
set output ARG1
set title "Accuracy vs Training Size"
set xlabel "Training Size (%)"
set ylabel "Accuracy (%)"
plot ARG2 using 1:2 title "" with linespoints