#!/bin/bash

METRICAS="L3CACHE ENERGY FLOPS_DP"

if [ ! -d "results" ]; then
    mkdir results
fi
if [ ! -d "results/v1" ]; then
    mkdir results/v1
fi
if [ ! -d "results/v2" ]; then
    mkdir results/v2
fi

make all

echo "n,k,version,time1,time2" > "results/time.csv"

n=10
#K="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000"
K="64 128 200 256"
for k in $K
do
    ./gera $k $n > entrada.in
    # getting time (no need for likwid)
    ./ajustePolV1 < entrada.in | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",1,"$tempo_monta","$tempo_elimina >> results/time.csv
    ./ajustePolV2 < entrada.in | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",2,"$tempo_monta","$tempo_elimina >> results/time.csv
    for metrica in $METRICAS
    do
        nome_arq=($metrica"_"$k"_"$n".csv")
        echo $nome_arq

        # results for v1
        cat entrada.in | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV1 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v1/$nome_arq

        # results for v2
        cat entrada.in | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV2 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v2/$nome_arq
    done
done

n=1000
#K="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000"
K="64 128 200 256"
for k in $K
do
    ./gera $k $n > entrada.in
    # getting time (no need for likwid)
    ./ajustePolV1 < entrada.in | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",1,"$tempo_monta","$tempo_elimina >> results/time.csv
    ./ajustePolV2 < entrada.in | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",2,"$tempo_monta","$tempo_elimina >> results/time.csv
    for metrica in $METRICAS
    do
        nome_arq=($metrica"_"$k"_"$n".csv")
        echo $nome_arq

        # results for v1
        cat entrada.in | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV1 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v1/$nome_arq

        # results for v2
        cat entrada.in | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV2 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v2/$nome_arq
    done
done

rm temp.txt
rm entrada.in
make purge
