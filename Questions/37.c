// Problem Statement:
// Implement a Priority Queue using an array. An element with smaller value has higher priority.

// Supported Operations:
// - insert x
// - delete
// - peek

// Input Format:
// - First line contains integer N
// - Next N lines contain operations

// Output Format:
// - Print the deleted or peeked element
// - Print -1 if the queue is empty

// Example:
// Input:
// 5
// insert 30
// insert 10
// insert 20
// delete
// peek

// Output:
// 10
// 205
#include <stdio.h>
#include <limits.h>

#define MAX 1000

int pq[MAX];
int size = 0;

void insert(int x) {
    if (size >= MAX) return;
    pq[size++] = x;
}

int getMinIndex() {
    if (size == 0) return -1;
    int minIdx = 0;
    for (int i = 1; i < size; i++) {
        if (pq[i] < pq[minIdx]) {
            minIdx = i;
        }
    }
    return minIdx;
}

int delete() {
    if (size == 0) return -1;
    int minIdx = getMinIndex();
    int minValue = pq[minIdx];
    
    for (int i = minIdx; i < size - 1; i++) {
        pq[i] = pq[i + 1];
    }
    size--;
    return minValue;
}

int peek() {
    if (size == 0) return -1;
    int minIdx = getMinIndex();
    return pq[minIdx];
}

int main() {
    int n;
    scanf("%d", &n);
    char op[10];
    int val;
    
    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (op[0] == 'i') {
            scanf("%d", &val);
            insert(val);
        } else if (op[0] == 'd') {
            printf("%d\n", delete());
        } else if (op[0] == 'p') {
            printf("%d\n", peek());
        }
    }
    return 0;
}