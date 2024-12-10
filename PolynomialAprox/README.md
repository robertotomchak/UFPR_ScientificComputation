# Ajuste de Curvas Otimizado
## Informações do Aluno
- Nome: Roberto Sprengel Minozzo Tomchak
- GRR: 20232369

## Visão Geral
Esse trabalho tem como objetivo fazer o ajuste de curva de uma função baseada em k pontos coletados, usando o Método dos Mínimos Quadrados com ajuste polinomial de grau n.

Além disso, o objetivo é otimizar o algoritmo dado, de forma a aprender técnicas de otimização de código, e medir a eficiência dos algoritmos utilizados.

## Pré-requisitos
- É necessário ter Python instalado. Nenhuma biblioteca além das bibliotecas padrão da linguagem são usadas
- O projeto foi desenvolvido em Linux. Em outros SOs pode ser que não execute, devido ao uso de bash scripts e paths no padrão Linux (dir1/dir2/...)
- É necessário ter o likwid instalado. É possível que seja necessário alterar o LIKDWID_HOME no Makefile 

## Como usar
### Compilando códigos
```console
make all
```
### Gerando testes
```console
./gera_testes.sh
```
Os resultados dos testes serão salvos num diretório "results". O arquivo time.csv possui o resultado de tempo dos algoritmos, o diretório v1 os resultados usando likwid do algoritmo original, e o diretório v2 os resultados do algoritmo otimizado.

### Gerando gráficos
Caso o diretório "results" já exista com todos os resultados, execute:
```console
./gera_graficos.sh
```
Os gráficos serão salvos num diretório "graphics", com dois subdiretórios: "a", que contém os gráficos da parte a do algoritmo (montaSL), e o subdiretório "b", com os gráficos da parte b do algoritmo (resolveSL com eliminação de Gauss)

## Arquitetura usada
Dados obtidos com o comando 
```console
likwid-topology -g -c
```

Tipo da CPU: Intel Xeon SandyBridge EN/EP processor

Sockets: 2, cada uma com 8 cores e 1 thread por core

Cache: L1 (32 kB), L2 (256 kB) e L3 (20 MB)

Mais informações em topology.txt.

## Otimizações Feitas
- Array of structs: ao invés de ter um vetor x e um vetor y, foi criado um vetor que intercala os dois (x0, y0, x1, y2, ..., xn, yn). Essa otimização foi feita pois o acesso no código é feito pegando o valor x e seu respectivo y logo em seguida, logo assim é otimizado o uso da cache;
- Vetor de potências: ao invés de usar a função pow, é usado um vetor xk, que guarda cada x elevado a k. Assim, para obter x^(k+1), basta multiplicar xk por x. Isso evita o uso da função pow, que é lenta;
- Vetor temp: o cálculo de A[i][j] possui várias repetições. Por exemplo, A[1][0] = A[0][1]. Para evitar calcular a mesma coisa várias vezes, cada valor é calculado apenas uma vezes, armazenado em temp, e depois atribuído na matriz. Mais especificamente, temos que A[i][j] = temp[i+j], pois temp[i+j] = soma de todos os x^(i+j);
- Variáveis temporárias e shifts: sempre que possível, foi usado variáveis para evitar recalcular a mesma expressão várias vezes, e shifts no lugar de multiplicações/divisões por potências de 2. Isso ajuda a reduzir algumas operações de ponto flutuante e otimizar cálculos na CPU;
- Loop unrolling na Retrosubstituição: foi feito um loop unrolling de m=4 na etapa de retrosubstituição da Eliminação de Gauss. Entretanto, foi testado e analisado que o loop unrolling não trouxe resultados muito otimizados para nenhum m em {1, 2, 4};
- Restrict: os ponteiros usados comp parâmetros na montagem do SL (etapa A) foram declarados como restrict, o que ajudou na questão do alinhamento.

## Modificações Testadas mas não usadas
As seguintes modificações foram testadas, mas foram descartadas por não apresentarem bons resultados:

- Restrict na etapa b
- Loop unrolling na etapa a
- Loop unrolling em outros trechos da etapa b
- Representar matriz como vetor

## Analisando Resultados
Obs: para a etapa A, houve um pico de energia inusitado no v1 com n = 10. Para poder analisar melhor essa métrica, foicriado um gráfico que avalia a energia, mas com o eixo y em escala logarítmica, além do gráfico com esse eixo inalterado.

Analisando os resultados na etapa B, vemos que há pouca diferença entre v1 e v2. Isso acontece porque poucas modificações foram feitas no algoritmo (apenas loop unrolling na retrosubstituição). Entretanto, essa modificação já ajudou a ter alguns resultados. Apesar de pequena diferença, o v2 teve menos cache miss que o v1, o que refletiu numa pequena redução no tempo total do algoritmo para n = 10. Para n = 1000, parece que esse ganho de desempenho no uso da memória contribuiu pouco para o tempo dessa etapa.

Já na etapa A, o v2 é melhor que o v1 em todos os aspectos. O gasto energético é bem mais baixo, o número de MFLOPS/s caiu e o cache miss é consideravemente mais baixo, cerca de 2 vezes menor. O uso mais eficiente da memória e a realização de menos operações com ponto flutuante refletiu numa redução forte no tempo de execução de algumas ordens de magnitude (cerca de 100 ou 1000 vezes menor). Inclusive, a diferença é tão gritante que o v2 com n = 1000 se compara igualmente com o v1 com n = 10 em termos de tempo.

Embora não houve muita otimização na etapa B, o gargalo do algoritmo é justamente na etapa A. Vendo a escala de tempo dessas duas etapas, é possível notar que a magnitude do eixo y é bem maior na etapa A do que na etapa B. Assim, v2 conseguiu otimizar muito bem o ponto problemático do algoritmo sem trazer prejuízos.

Assim, é possível concluir que as otimizações de v2 foram benéficas para o algoritmo como um todo.

## Explicando Resultados de AVX Flops
Uma das métricas usadas nesse trabalho foi o AVX Flops, medido em MFLops/s. Essa métrica mostra o uso de operações de ponto flutuante que foram cálculados usando instruções vetoriais da CPU. Ou seja, cálculos que foram possíveis de serem vetorizados.

Os resultados podem ser encontrados em "graphics/a/FLOPS_AVX_DP.png" e "graphics/a/FLOPS_AVX_DP.png". É possível perceber que, na etapa A, o algoritmo v1 (versão original) não teve instruções vetoriais, enquanto a versão 2 (otimizada) teve. Isso ajudou no desempenho do algoritmo, uma vez que o processador conseguiu paralelizar vários cálculos a partir disso.

Já na etapa B, tanto v1 quanto v2 conseguiram paralelizar operações, mas com n=1000 houve muito mais operações vetoriais. A explicação provável desse fenômeno é que, com n=10, o sistema linear criado é muito pequeno, e portanto poucas operações são realizadas, enquanto com n=1000 o sistema linear é muito grande, então há necessidade de fazer mais operações. De maneira geral, parece que o número de operações vetoriais foi proporcional ao tamanho do SL, o que é bom, pois mostra que os algoritmos conseguem escalar bem com o tamanho do sistema linear dado.

