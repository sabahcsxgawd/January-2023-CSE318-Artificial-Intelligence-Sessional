#!/bin/bash

for i in $(ls ./318_offline_1/ | grep in)
do
    ./1905118 < $i > "ans${i:2}"
done