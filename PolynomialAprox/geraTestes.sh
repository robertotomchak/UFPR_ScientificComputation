#!/bin/bash

K="64 128 200 256"
n=256
METRICAS="L3CACHE ENERGY FLOPS_DP"

mkdir results

for metrica in $METRICAS
do
    for k in $K
    do
        temp_in=$(./gera $k $n)
        nome_arq=($metrica"_"$k"_"$n".txt")
        echo $nome_arq
        echo $temp_in | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV2 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/$nome_arq
    done
done
