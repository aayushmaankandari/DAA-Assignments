#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} MaxHeap;

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void heapify(MaxHeap *h, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < h->size && h->arr[l] > h->arr[largest]) largest = l;
    if (r < h->size && h->arr[r] > h->arr[largest]) largest = r;
    if (largest != i) { swap(&h->arr[i], &h->arr[largest]); heapify(h, largest); }
}

int extractMax(MaxHeap *h) {
    int max = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return max;
}

void insert(MaxHeap *h, int val) {
    h->size++;
    int i = h->size - 1;
    h->arr[i] = val;
    while (i && h->arr[i] > h->arr[(i-1)/2]) {
        swap(&h->arr[i], &h->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = 4;
    MaxHeap h = {malloc(n * sizeof(int)), 0};

    int minVal = 1e9;
    for (int i = 0; i < n; i++) {
        int val = arr[i];
        if (val % 2) val *= 2;
        insert(&h, val);
        if (val < minVal) minVal = val;
    }

    int deviation = 1e9;
    while (h.size) {
        int maxVal = extractMax(&h);
        deviation = (maxVal - minVal < deviation) ? maxVal - minVal : deviation;
        if (maxVal % 2 == 0) {
            maxVal /= 2;
            if (maxVal < minVal) minVal = maxVal;
            insert(&h, maxVal);
        } else break;
    }

    printf("Minimum deviation: %d\n", deviation);
    free(h.arr);
    return 0;
}
