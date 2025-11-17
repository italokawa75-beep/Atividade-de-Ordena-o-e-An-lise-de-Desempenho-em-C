#ifndef SORTS_H       // Se SORTS_H ainda não estiver definido
#define SORTS_H       // define SORTS_H para evitar múltiplas inclusões

#include <stddef.h>   // Biblioteca para tipos como size_t (tipo inteiro sem sinal)

// ------------------- Estrutura de Métricas -------------------
// Armazena contadores para analisar desempenho dos algoritmos
typedef struct {
    long long steps_cmp;   // número de comparações feitas
    long long steps_swap;  // número de trocas ou movimentos feitos
} Metrics;

// ------------------- Funções -------------------

// Zera os contadores de métricas
void reset_metrics(Metrics *m);

// Algoritmos de ordenação
void insertion_sort(int *v, size_t n, Metrics *m); // Insertion Sort
void merge_sort(int *v, size_t n, Metrics *m);     // Merge Sort
void quick_sort(int *v, size_t n, Metrics *m);     // Quick Sort usando partição Lomuto

#endif  // Fim do #ifndef SORTS_H
