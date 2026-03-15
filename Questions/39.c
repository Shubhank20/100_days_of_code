// Problem Statement:
// Implement a Min Heap using an array where the smallest element is always at the root.

// Supported Operations:
// - insert x
// - extractMin
// - peek

// Input Format:
// - First line contains integer N
// - Next N lines contain heap operations

// Output Format:
// - Print results of extractMin and peek
// - Print -1 if operation cannot be performed

// Example:
// Input:
// 6
// insert 40
// insert 10
// insert 30
// peek
// extractMin
// peek

// Output:
// 10
// 10
// 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int heap[MAX];
int size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            swap(&heap[parent], &heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void insert(int x) {
    if (size >= MAX) return;
    heap[size] = x;
    heapifyUp(size);
    size++;
}

int extractMin() {
    if (size == 0) return -1;
    int min = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return min;
}

int peek() {
    if (size == 0) return -1;
    return heap[0];
}

int main() {
    int n;
    scanf("%d", &n);
    char op[10];
    int val;
    
    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (strcmp(op, "insert") == 0) {
            scanf("%d", &val);
            insert(val);
        } else if (strcmp(op, "extractMin") == 0) {
            printf("%d\n", extractMin());
        } else if (strcmp(op, "peek") == 0) {
            printf("%d\n", peek());
        }
    }
    return 0;
}