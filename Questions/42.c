// Problem Statement:
// Given a queue of integers, reverse the queue using a stack.

// Input Format:
// - First line contains integer N
// - Second line contains N space-separated integers

// Output Format:
// - Print the reversed queue

// Example:
// Input:
// 5
// 10 20 30 40 50

// Output:
// 50 40 30 20 10
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = val;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return val;
}

void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int val) {
    s->arr[++s->top] = val;
}

int pop(Stack* s) {
    if (isStackEmpty(s)) return -1;
    return s->arr[s->top--];
}

int main() {
    Queue q;
    Stack s;
    initQueue(&q);
    initStack(&s);

    int n, val;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(&q, val);
    }

    while (!isQueueEmpty(&q)) {
        push(&s, dequeue(&q));
    }

    while (!isStackEmpty(&s)) {
        int v = pop(&s);
        printf("%d ", v);
        enqueue(&q, v);
    }
    printf("\n");

    return 0;
}