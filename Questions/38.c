// Problem: Deque (Double-Ended Queue)

// A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

// Common Operations:
// 1. push_front(value): Insert an element at the front of the deque.
// 2. push_back(value): Insert an element at the rear of the deque.
// 3. pop_front(): Remove an element from the front of the deque.
// 4. pop_back(): Remove an element from the rear of the deque.
// 5. front(): Return the front element of the deque.
// 6. back(): Return the rear element of the deque.
// 7. empty(): Check whether the deque is empty.
// 8. size(): Return the number of elements in the deque.

// Additional Operations:
// - clear(): Remove all elements from the deque.
// - erase(): Remove one or more elements from the deque.
// - swap(): Swap contents of two deques.
// - emplace_front(): Insert an element at the front without copying.
// - emplace_back(): Insert an element at the rear without copying.
// - resize(): Change the size of the deque.
// - assign(): Replace elements with new values.
// - reverse(): Reverse the order of elements.
// - sort(): Sort the elements in ascending order.

// Time Complexity:
// - push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
// - clear, erase, resize, assign, reverse: O(n)
// - sort: O(n log n)

// Input:
// - Sequence of deque operations with values (if applicable)

// Output:
// - Results of operations such as front, back, size, or the final state of the deque after all operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct {
    int data[MAX];
    int front;
    int rear;
    int count;
} Deque;

void initDeque(Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
    dq->count = 0;
}

int isEmpty(Deque* dq) {
    return dq->count == 0;
}

int isFull(Deque* dq) {
    return dq->count == MAX;
}

void push_front(Deque* dq, int val) {
    if (isFull(dq)) return;
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX - 1;
    } else {
        dq->front--;
    }
    dq->data[dq->front] = val;
    dq->count++;
}

void push_back(Deque* dq, int val) {
    if (isFull(dq)) return;
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == MAX - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    dq->data[dq->rear] = val;
    dq->count++;
}

int pop_front(Deque* dq) {
    if (isEmpty(dq)) return -1;
    int val = dq->data[dq->front];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == MAX - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
    dq->count--;
    return val;
}

int pop_back(Deque* dq) {
    if (isEmpty(dq)) return -1;
    int val = dq->data[dq->rear];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = MAX - 1;
    } else {
        dq->rear--;
    }
    dq->count--;
    return val;
}

int front(Deque* dq) {
    if (isEmpty(dq)) return -1;
    return dq->data[dq->front];
}

int back(Deque* dq) {
    if (isEmpty(dq)) return -1;
    return dq->data[dq->rear];
}

int size(Deque* dq) {
    return dq->count;
}

void printDeque(Deque* dq) {
    if (isEmpty(dq)) {
        printf("-1\n");
        return;
    }
    int i = dq->front;
    while (1) {
        printf("%d ", dq->data[i]);
        if (i == dq->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Deque dq;
    initDeque(&dq);
    char op[20];
    int val;

    while (1) {
        scanf("%s", op);
        if (strcmp(op, "push_front") == 0) {
            scanf("%d", &val);
            push_front(&dq, val);
        } else if (strcmp(op, "push_back") == 0) {
            scanf("%d", &val);
            push_back(&dq, val);
        } else if (strcmp(op, "pop_front") == 0) {
            printf("%d\n", pop_front(&dq));
        } else if (strcmp(op, "pop_back") == 0) {
            printf("%d\n", pop_back(&dq));
        } else if (strcmp(op, "front") == 0) {
            printf("%d\n", front(&dq));
        } else if (strcmp(op, "back") == 0) {
            printf("%d\n", back(&dq));
        } else if (strcmp(op, "size") == 0) {
            printf("%d\n", size(&dq));
        } else if (strcmp(op, "empty") == 0) {
            printf("%d\n", isEmpty(&dq));
        } else if (strcmp(op, "print") == 0) {
            printDeque(&dq);
        } else if (strcmp(op, "stop") == 0) {
            break;
        }
    }
    return 0;
}