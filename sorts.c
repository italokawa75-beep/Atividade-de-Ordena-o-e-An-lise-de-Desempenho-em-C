#include "sorts.h"
#include <stdlib.h>

// ------------------- Métricas -------------------
void reset_metrics(Metrics *m) {
    m->steps_cmp = 0;
    m->steps_swap = 0;
}

// ------------------- Insertion Sort -------------------
void insertion_sort(int *v, size_t n, Metrics *m) {
    for(size_t i=1;i<n;i++) {
        int key = v[i];
        size_t j = i;
        while(j>0) {
            m->steps_cmp++;
            if(v[j-1] > key) {
                v[j] = v[j-1];
                m->steps_swap++;
            } else break;
            j--;
        }
        v[j] = key;
        m->steps_swap++;
    }
}

// ------------------- Merge Sort -------------------
static void merge(int *v, size_t l, size_t m, size_t r, Metrics *met) {
    size_t n1 = m-l+1, n2 = r-m;
    int *L = malloc(sizeof(int)*n1);
    int *R = malloc(sizeof(int)*n2);
    for(size_t i=0;i<n1;i++) L[i]=v[l+i];
    for(size_t i=0;i<n2;i++) R[i]=v[m+1+i];

    size_t i=0,j=0,k=l;
    while(i<n1 && j<n2) {
        met->steps_cmp++;
        if(L[i]<=R[j]) { v[k]=L[i++]; met->steps_swap++; }
        else { v[k]=R[j++]; met->steps_swap++; }
        k++;
    }
    while(i<n1) { v[k++]=L[i++]; met->steps_swap++; }
    while(j<n2) { v[k++]=R[j++]; met->steps_swap++; }
    free(L); free(R);
}

static void merge_sort_rec(int *v, size_t l, size_t r, Metrics *met) {
    if(l<r) {
        size_t mid = l + (r-l)/2;
        merge_sort_rec(v,l,mid,met);
        merge_sort_rec(v,mid+1,r,met);
        merge(v,l,mid,r,met);
    }
}

void merge_sort(int *v, size_t n, Metrics *met) {
    reset_metrics(met);
    merge_sort_rec(v,0,n-1,met);
}

// ------------------- Quick Sort (Lomuto) -------------------
static size_t partition(int *v, size_t low, size_t high, Metrics *met) {
    int pivot = v[high];
    size_t i = low;
    for(size_t j=low;j<high;j++) {
        met->steps_cmp++;
        if(v[j]<=pivot) {
            int tmp=v[i]; v[i]=v[j]; v[j]=tmp;
            met->steps_swap++;
            i++;
        }
    }
    int tmp=v[i]; v[i]=v[high]; v[high]=tmp;
    met->steps_swap++;
    return i;
}

static void quick_sort_rec(int *v, size_t low, size_t high, Metrics *met) {
    if(low<high) {
        size_t pi = partition(v,low,high,met);
        if(pi>0) quick_sort_rec(v,low,pi-1,met);
        quick_sort_rec(v,pi+1,high,met);
    }
}

void quick_sort(int *v, size_t n, Metrics *met) {
    reset_metrics(met);
    if(n>0) quick_sort_rec(v,0,n-1,met);
}
