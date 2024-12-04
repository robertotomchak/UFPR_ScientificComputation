#!/bin/bash

K="64 128 200 256"
n=1024

for k in $K
do
    temp_in=$(./gera $k $n)
    echo $temp_in | likwid-perfctr -O -C 3 -g ENERGY -m ./ajustePolV2 > temp.txt
    tail temp.txt -n10
done
