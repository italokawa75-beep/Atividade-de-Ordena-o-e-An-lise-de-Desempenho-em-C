#include <stdio.h> // biblioteca de entrada e saida de dados
#include <stdlib.h> //biblioteca padrao de manipulação de memoria 
#include <string.h> //biblioteca para manipular strings
#include <time.h>//biblioteca de manipulação de data e horarios
#include "sorts.h" //biblioteca que inclui o arquivo sort.h
 
// ------------------- Função para medir tempo -------------------
// Recebe uma função de ordenação, vetor e métricas.
// Retorna o tempo em milissegundos que a função levou para ordenar.
double run_sort(void (*fn)(int*,size_t,Metrics*), int *v, size_t n, Metrics *m) {
    reset_metrics(m);           // Zera os contadores de comparação e troca
    clock_t t0 = clock();       // Marca o tempo inicial
    fn(v,n,m);                  // Executa a ordenação
    clock_t t1 = clock();       // Marca o tempo final
    return 1000.0*(t1-t0)/CLOCKS_PER_SEC; // Converte para ms
}

// ------------------- Funções auxiliares -------------------
// Gera um vetor aleatório de tamanho n, com valores até 9999
int* gerarVetor(size_t n) {
    int *v = malloc(sizeof(int)*n);
    for(size_t i=0;i<n;i++) v[i]=rand()%10000;
    return v;
}

// Copia um vetor v de tamanho n
int* copiaVetor(int *v, size_t n) {
    int *c = malloc(sizeof(int)*n);
    memcpy(c,v,sizeof(int)*n);
    return c;
}

// Converte uma string de RGM em vetor de inteiros (cada dígito)
int* rgmParaVetor(const char *rgm, size_t *n) {
    *n = strlen(rgm);
    int *v = malloc(sizeof(int)*(*n));
    for(size_t i=0;i<*n;i++) v[i]=rgm[i]-'0'; // '0' converte char para int
    return v;
}

// Imprime resultados em formato CSV
void printCSV(const char *metodo, size_t N, const char *caso, Metrics m, double tempo_ms) {
    printf("%s,%zu,%s,%lld,%lld,%.3f\n",
           metodo,N,caso,m.steps_cmp,m.steps_swap,tempo_ms);
}

// ------------------- Função principal -------------------
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    char rgm[100];
    printf("Digite seu RGM: "); 
    scanf("%s",rgm);  // Lê o RGM do usuário

    // Cabeçalho do CSV
    printf("metodo,N,caso,steps_cmp,steps_swap,tempo_ms\n");

    size_t nRGM; 
    Metrics m; 
    int *vTemp;

    // Converte o RGM para vetor de inteiros
    int *vRGM = rgmParaVetor(rgm,&nRGM);

    // ---------- Ordenação do vetor RGM ----------
    vTemp = copiaVetor(vRGM,nRGM); 
    double t = run_sort(insertion_sort,vTemp,nRGM,&m); 
    printCSV("insertion",nRGM,"RGM",m,t); 
    free(vTemp);

    vTemp = copiaVetor(vRGM,nRGM); 
    t = run_sort(merge_sort,vTemp,nRGM,&m); 
    printCSV("merge",nRGM,"RGM",m,t); 
    free(vTemp);

    vTemp = copiaVetor(vRGM,nRGM); 
    t = run_sort(quick_sort,vTemp,nRGM,&m); 
    printCSV("quick",nRGM,"RGM",m,t); 
    free(vTemp);

    free(vRGM); // Libera memória do vetor RGM

    // ---------- Ordenação de vetores aleatórios ----------
    size_t tamanhos[] = {100,1000,10000};
    for(int i=0;i<3;i++){
        size_t N = tamanhos[i];
        int *vRand = gerarVetor(N); // Gera vetor aleatório

        // Testa os três algoritmos no vetor aleatório
        vTemp = copiaVetor(vRand,N); 
        t = run_sort(insertion_sort,vTemp,N,&m); 
        printCSV("insertion",N,"aleatorio",m,t); 
        free(vTemp);

        vTemp = copiaVetor(vRand,N); 
        t = run_sort(merge_sort,vTemp,N,&m); 
        printCSV("merge",N,"aleatorio",m,t); 
        free(vTemp);

        vTemp = copiaVetor(vRand,N); 
        t = run_sort(quick_sort,vTemp,N,&m); 
        printCSV("quick",N,"aleatorio",m,t); 
        free(vTemp);

        free(vRand); // Libera memória do vetor aleatório
    }

    return 0;
}
