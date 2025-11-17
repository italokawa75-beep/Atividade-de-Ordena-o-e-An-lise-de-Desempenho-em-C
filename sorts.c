#include "sorts.h"    // Inclui o arquivo com declarações das funções de ordenação e da struct Metrics
#include <stdlib.h>   // Biblioteca padrão do C para funções como malloc, free, rand, etc.

// ------------------- Métricas -------------------
// Zera os contadores de comparações e trocas
void reset_metrics(Metrics *m) {
    m->steps_cmp = 0;
    m->steps_swap = 0;
}

// ------------------- Insertion Sort -------------------
// Ordena o vetor 'v' de tamanho 'n' usando o método Insertion Sort
// Atualiza métricas de comparações e trocas
void insertion_sort(int *v, size_t n, Metrics *m) {
    for(size_t i=1;i<n;i++) {
        int key = v[i];      // elemento atual a ser inserido
        size_t j = i;
        while(j>0) {
            m->steps_cmp++;  // conta comparação
            if(v[j-1] > key) { 
                v[j] = v[j-1]; // move elemento maior para a direita
                m->steps_swap++; // conta troca/movimento
            } else break;
            j--;
        }
        v[j] = key;           // insere o elemento na posição correta
        m->steps_swap++;
    }
}

// ------------------- Merge Sort -------------------
// Função auxiliar que faz a fusão de duas metades do vetor
static void merge(int *v, size_t l, size_t m, size_t r, Metrics *met) {
    size_t n1 = m-l+1, n2 = r-m;
    int *L = malloc(sizeof(int)*n1); // cria subvetor esquerdo
    int *R = malloc(sizeof(int)*n2); // cria subvetor direito
    for(size_t i=0;i<n1;i++) L[i]=v[l+i];
    for(size_t i=0;i<n2;i++) R[i]=v[m+1+i];

    size_t i=0,j=0,k=l;
    while(i<n1 && j<n2) {
        met->steps_cmp++; // conta comparação
        if(L[i]<=R[j]) { 
            v[k]=L[i++]; 
            met->steps_swap++;
        }
        else { 
            v[k]=R[j++]; 
            met->steps_swap++;
        }
        k++;
    }
    while(i<n1) { v[k++]=L[i++]; met->steps_swap++; }
    while(j<n2) { v[k++]=R[j++]; met->steps_swap++; }

    free(L); free(R); // libera memória dos subvetores
}

// Função recursiva do Merge Sort
static void merge_sort_rec(int *v, size_t l, size_t r, Metrics *met) {
    if(l<r) {
        size_t mid = l + (r-l)/2;
        merge_sort_rec(v,l,mid,met);      // ordena metade esquerda
        merge_sort_rec(v,mid+1,r,met);    // ordena metade direita
        merge(v,l,mid,r,met);             // une as duas metades
    }
}

// Função principal Merge Sort
void merge_sort(int *v, size_t n, Metrics *met) {
    reset_metrics(met);                   // zera métricas antes de começar
    merge_sort_rec(v,0,n-1,met);          // chama recursão
}

// ------------------- Quick Sort (Lomuto) -------------------
// Particiona o vetor em torno do pivô
static size_t partition(int *v, size_t low, size_t high, Metrics *met) {
    int pivot = v[high];                   // escolhe pivô como último elemento
    size_t i = low;
    for(size_t j=low;j<high;j++) {
        met->steps_cmp++;                   // conta comparação
        if(v[j]<=pivot) {
            int tmp=v[i]; v[i]=v[j]; v[j]=tmp; // troca elementos menores que pivô
            met->steps_swap++;
            i++;
        }
    }
    int tmp=v[i]; v[i]=v[high]; v[high]=tmp; // coloca pivô na posição correta
    met->steps_swap++;
    return i;                               // retorna índice do pivô
}

// Função recursiva do Quick Sort
static void quick_sort_rec(int *v, size_t low, size_t high, Metrics *met) {
    if(low<high) {
        size_t pi = partition(v,low,high,met);
        if(pi>0) quick_sort_rec(v,low,pi-1,met);  // ordena esquerda
        quick_sort_rec(v,pi+1,high,met);          // ordena direita
    }
}

// Função principal Quick Sort
void quick_sort(int *v, size_t n, Metrics *met) {
    reset_metrics(met);                  // zera métricas
    if(n>0) quick_sort_rec(v,0,n-1,met);
}
