#ifndef SORTS_H
#define SORTS_H

#include <stddef.h>

typedef struct {
    long long steps_cmp;   // comparações
    long long steps_swap;  // movimentos/trocas
} Metrics;

void reset_metrics(Metrics *m);

// Ordenações
void insertion_sort(int *v, size_t n, Metrics *m);
void merge_sort(int *v, size_t n, Metrics *m);
void quick_sort(int *v, size_t n, Metrics *m); // Lomuto

#endif
