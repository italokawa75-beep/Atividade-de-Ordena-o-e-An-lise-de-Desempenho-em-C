 1. Descrição do Problema

O objetivo desta atividade é:
Converter o RGM do aluno em um vetor para a ordem crescente.
Ordenar esses dígitos em ordem crescente utilizando 3 métodos de ordenação escolhidos.
Comparar desempenho com base em:
número de comparações (steps_cmp)
movimentações/trocas (steps_swap)
tempo de execução em milissegundos (tempo_ms)
Repetir os testes em vetores aleatórios de tamanhos maiores.
Exportar tudo em formato CSV.
Realizar análise crítica dos resultados.


    2.Como Compilar e Executar
    
 Compilar localmente (Linux/Windows com GCC)
Na raiz do projeto:
gcc -O1 -std=c11 main.c sorts.c -o ordena
Executar:
./ordena .


    3.Como Executar no OnlineGDB

Acesse: https://www.onlinegdb.com/online_c_compiler
Clique em New ou abra um projeto em C.
Copie o conteúdo de main.c para a aba principal.
Clique no botão Add new file e crie:
sorts.c
sorts.h
Cole o conteúdo de cada arquivo corretamente.
No canto superior, selecione Debug / Run.
O programa pedirá o RGM e depois exibirá a saída em CSV no console.
Obs.: O OnlineGDB compila automaticamente, não é necessário escrever o comando gcc.


 4.Política de Contagem de Passos & Medição de Tempo
  
 Contagem de passos
A struct Metrics contém:
steps_cmp → incrementa sempre que ocorre uma comparação lógica entre elementos.
steps_swap → incrementa a cada troca/movimentação de elementos
Cada algoritmo mantém sua lógica própria, mas usa a mesma política.
Medição de tempo de execução
Utiliza clock().

5.REsultado:

Digite seu RGM: 56749498
metodo,N,caso,steps_cmp,steps_swap,tempo_ms
insertion,8,RGM,15,16,0.002
merge,8,RGM,15,24,0.002
quick,8,RGM,14,12,0.000
insertion,100,aleatorio,2592,2593,0.012
merge,100,aleatorio,545,672,0.015
quick,100,aleatorio,607,421,0.011
insertion,1000,aleatorio,247980,247986,1.056
merge,1000,aleatorio,8694,9976,0.181
quick,1000,aleatorio,10712,6632,0.102
insertion,10000,aleatorio,25402704,25402713,83.216
merge,10000,aleatorio,120473,133616,1.715
quick,10000,aleatorio,152470,84557,1.143

6.Discussão

Durante os testes deu para perceber bem como cada algoritmo reage a diferentes tamanhos de entrada.
O Insertion Sort funcionou tranquilo para o RGM, que tem poucos elementos, mas para vetores maiores ele ficou muito lento, porque sua quantidade de passos cresce muito rápido (O(n²)).
O Merge Sort se mostrou bem estável. Ele manteve um tempo de execução bom mesmo nos vetores grandes, já que sua complexidade é O(n log n). A única desvantagem é usar memória extra para os vetores auxiliares.
O Quick Sort acabou sendo o que teve o melhor desempenho geral. Para os vetores aleatórios ele foi mais rápido que os outros dois. Mesmo podendo cair no pior caso, isso não aconteceu nos testes e ele se saiu muito bem.
 Conclusão geral
Quick Sort foi o mais rápido na prática.
Merge Sort manteve o desempenho mais consistente.
Insertion Sort só é bom para vetores pequenos (como o RGM).
Essas diferenças mostram bem a questão de escalabilidade: algoritmos quadráticos não escalam bem, enquanto os O(n log n) lidam melhor com grandes volumes.
