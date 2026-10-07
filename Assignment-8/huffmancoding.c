#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    char symbol;
    int freq;
    struct Node *left, *right;
} Node;

// Min-heap for priority queue
typedef struct {
    Node **arr;
    int size;
    int capacity;
} MinHeap;

Node* newNode(char symbol, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = symbol;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (Node**)malloc(capacity * sizeof(Node*));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < heap->size && heap->arr[l]->freq < heap->arr[smallest]->freq)
        smallest = l;
    if (r < heap->size && heap->arr[r]->freq < heap->arr[smallest]->freq)
        smallest = r;

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

Node* extractMin(MinHeap* heap) {
    Node* temp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return temp;
}

void insertHeap(MinHeap* heap, Node* node) {
    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = node;

    while (i && heap->arr[i]->freq < heap->arr[(i-1)/2]->freq) {
        swap(&heap->arr[i], &heap->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

Node* buildHuffman(char symbols[], int freq[], int n) {
    MinHeap* heap = createHeap(n);
    for (int i = 0; i < n; i++)
        insertHeap(heap, newNode(symbols[i], freq[i]));

    while (heap->size > 1) {
        Node* left = extractMin(heap);
        Node* right = extractMin(heap);

        Node* merged = newNode('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        insertHeap(heap, merged);
    }
    return extractMin(heap);
}

void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->symbol);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

int main() {
    char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(symbols)/sizeof(symbols[0]);

    Node* root = buildHuffman(symbols, freq, n);

    int arr[100], top = 0;
    printf("Huffman Codes:\n");
    printCodes(root, arr, top);

    return 0;
}
