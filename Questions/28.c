// Problem: Circular Linked List Creation and Traversal - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n
// - Second line: n space-separated integers

// Output:
// - Print the circular linked list elements starting from head, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50

// Output:
// 10 20 30 40 50

// Explanation:
// Last node's next points to head. Traverse from head until returning to head to avoid infinite loop.
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createCircularList(int arr[], int n) {
    if (n == 0) return NULL;

    struct Node *head = (struct Node*)malloc(sizeof(struct Node));
    head->data = arr[0];
    struct Node *current = head;

    for (int i = 1; i < n; i++) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        current->next = newNode;
        current = newNode;
    }

    current->next = head;

    return head;
}

void traverseCircularList(struct Node *head) {
    if (head == NULL) {
        return;
    }

    struct Node *temp = head;

    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    
    printf("\n");
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    if (n < 0) n = 0;

    int *arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node *head = createCircularList(arr, n);

    traverseCircularList(head);

    free(arr);
    return 0;
}