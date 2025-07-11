#!/bin/bash

# O QUE ALTERAR (SE NECESSÁRIO)
# METRICAS: métricas do likwid a serem usadas (nome exato usado pelo likwid)
# n e k: em ambos os loops, colocar valores que deseja
# nome das pastas: mais chato de mudar, todo lugar que tiver "results" e "v1" e "v2"
# nome dos executáveis: originalmente, ajustePolV1 (professor) e ajustePolV2 (otimizado)


METRICAS="L3CACHE ENERGY FLOPS_DP"

# criando pastas de resultados
if [ ! -d "results" ]; then
    mkdir results
fi
# resultados professor
if [ ! -d "results/v1" ]; then
    mkdir results/v1
fi
# resultados otimizado
if [ ! -d "results/v2" ]; then
    mkdir results/v2
fi

# compila os códigos
make all

# cria csv com resultados do tempo (tanto de v1 quanto v2)
echo "n,k,version,time1,time2" > "results/time.csv"

# testes com n = 10
n=10
K="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000"
for k in $K
do
    # getting time (no need for likwid)
    ./gera $k $n | ./ajustePolV1 | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",1,"$tempo_monta","$tempo_elimina >> results/time.csv
    ./gera $k $n | ./ajustePolV2 | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",2,"$tempo_monta","$tempo_elimina >> results/time.csv
    # para cada métrica, cria um csv com aquela métrica e os respectivos k e n
    for metrica in $METRICAS
    do
        nome_arq=($metrica"_"$k"_"$n".csv")
        echo $nome_arq

        # results for v1
        ./gera $k $n | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV1 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v1/$nome_arq

        # results for v2
        ./gera $k $n | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV2 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v2/$nome_arq
    done
done

# testes com n = 1000
n=1000
K="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000"
for k in $K
do
    # getting time (no need for likwid)
    ./gera $k $n | ./ajustePolV1 | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",1,"$tempo_monta","$tempo_elimina >> results/time.csv
    ./gera $k $n | ./ajustePolV2 | tail -n1 > temp.txt
    tempo_monta=$(cut -d' ' temp.txt -f2)
    tempo_elimina=$(cut -d' ' temp.txt -f3)
    echo $n","$k",2,"$tempo_monta","$tempo_elimina >> results/time.csv
    # para cada métrica, cria um csv com aquela métrica e os respectivos k e n
    for metrica in $METRICAS
    do
        nome_arq=($metrica"_"$k"_"$n".csv")
        echo $nome_arq

        # results for v1
        ./gera $k $n | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV1 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v1/$nome_arq

        # results for v2
        ./gera $k $n | likwid-perfctr -O -C 3 -g $metrica -m ./ajustePolV2 > temp.txt
        tam=$(wc -l temp.txt | cut -d' ' -f1)
        inicio=$(grep '\-\-' temp.txt -n | tail -n1 | cut -d':' -f1)
        pegar=$(($tam-$inicio))
        tail -n$pegar temp.txt > results/v2/$nome_arq
    done
done

rm temp.txt
make purge
