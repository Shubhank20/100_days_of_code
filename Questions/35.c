// Problem: Queue Using Array - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n (number of elements)
// - Second line: n space-separated integers

// Output:
// - Print queue elements from front to rear, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50

// Output:
// 10 20 30 40 50

// Explanation:
// Use array and front/rear pointers. Enqueue inserts at rear, dequeue removes from front. Display from front to rear.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int front;
    int rear;
    int *arr;
    int capacity;
} Queue;

// Function to create a queue with given capacity
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->arr = (int*)malloc(capacity * sizeof(int));
    return q;
}

// Function to add an element to the queue
void enqueue(Queue* q, int value) {
    if (q->rear == q->capacity - 1) {
        return; // Queue is full (though problem input fits exactly)
    }
    q->rear++;
    q->arr[q->rear] = value;
}

// Function to display elements from front to rear
void display(Queue* q) {
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d", q->arr[i]);
        if (i < q->rear) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n, val;

    // Read number of elements
    scanf("%d", &n);

    // Create queue with capacity n
    Queue* q = createQueue(n);

    // Read elements and enqueue them
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(q, val);
    }

    // Print the queue
    display(q);

    // Free allocated memory
    free(q->arr);
    free(q);

    return 0;
}