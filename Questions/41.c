// Problem Statement:
// Implement a Queue using a linked list supporting enqueue and dequeue operations.

// Input Format:
// - First line contains integer N
// - Next N lines contain queue operations

// Output Format:
// - Print dequeued elements
// - Print -1 if dequeue is attempted on an empty queue
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(Queue* q, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("-1\n");
        return;
    }
    Node* temp = q->front;
    printf("%d\n", temp->data);
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

int main() {
    Queue q;
    initQueue(&q);
    int n, val;
    char op[10];
    scanf("%d", &n);
    while (getchar() != '\n');
    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (op[0] == 'e') {
            scanf("%d", &val);
            enqueue(&q, val);
        } else if (op[0] == 'd') {
            dequeue(&q);
        }
    }
    return 0;
}