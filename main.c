#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorts.h"

// ------------------- Medir tempo -------------------
double run_sort(void (*fn)(int*,size_t,Metrics*), int *v, size_t n, Metrics *m) {
    reset_metrics(m);
    clock_t t0 = clock();
    fn(v,n,m);
    clock_t t1 = clock();
    return 1000.0*(t1-t0)/CLOCKS_PER_SEC;
}

// ------------------- Funções auxiliares -------------------
int* gerarVetor(size_t n) {
    int *v = malloc(sizeof(int)*n);
    for(size_t i=0;i<n;i++) v[i]=rand()%10000;
    return v;
}

int* copiaVetor(int *v, size_t n) {
    int *c = malloc(sizeof(int)*n);
    memcpy(c,v,sizeof(int)*n);
    return c;
}

int* rgmParaVetor(const char *rgm, size_t *n) {
    *n = strlen(rgm);
    int *v = malloc(sizeof(int)*(*n));
    for(size_t i=0;i<*n;i++) v[i]=rgm[i]-'0';
    return v;
}

void printCSV(const char *metodo, size_t N, const char *caso, Metrics m, double tempo_ms) {
    printf("%s,%zu,%s,%lld,%lld,%.3f\n",
           metodo,N,caso,m.steps_cmp,m.steps_swap,tempo_ms);
}

// ------------------- Main -------------------
int main() {
    srand(time(NULL));

    char rgm[100];
    printf("Digite seu RGM: "); scanf("%s",rgm);

    printf("metodo,N,caso,steps_cmp,steps_swap,tempo_ms\n");

    size_t nRGM; Metrics m; int *vTemp;
    int *vRGM = rgmParaVetor(rgm,&nRGM);

    // RGM
    vTemp = copiaVetor(vRGM,nRGM);
    double t = run_sort(insertion_sort,vTemp,nRGM,&m); printCSV("insertion",nRGM,"RGM",m,t); free(vTemp);

    vTemp = copiaVetor(vRGM,nRGM);
    t = run_sort(merge_sort,vTemp,nRGM,&m); printCSV("merge",nRGM,"RGM",m,t); free(vTemp);

    vTemp = copiaVetor(vRGM,nRGM);
    t = run_sort(quick_sort,vTemp,nRGM,&m); printCSV("quick",nRGM,"RGM",m,t); free(vTemp);

    free(vRGM);

    // Aleatórios
    size_t tamanhos[] = {100,1000,10000};
    for(int i=0;i<3;i++){
        size_t N = tamanhos[i];
        int *vRand = gerarVetor(N);

        vTemp = copiaVetor(vRand,N); t = run_sort(insertion_sort,vTemp,N,&m); printCSV("insertion",N,"aleatorio",m,t); free(vTemp);
        vTemp = copiaVetor(vRand,N); t = run_sort(merge_sort,vTemp,N,&m); printCSV("merge",N,"aleatorio",m,t); free(vTemp);
        vTemp = copiaVetor(vRand,N); t = run_sort(quick_sort,vTemp,N,&m); printCSV("quick",N,"aleatorio",m,t); free(vTemp);

        free(vRand);
    }

    return 0;
}
