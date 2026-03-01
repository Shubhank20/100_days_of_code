// Problem: Rotate Linked List Right by k Places - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n
// - Second line: n space-separated integers
// - Third line: integer k

// Output:
// - Print the linked list elements after rotation, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50
// 2

// Output:
// 40 50 10 20 30

// Explanation:
// Connect last node to head forming circular list. Traverse to (n-k)th node, set next to NULL, update head to (n-k+1)th node.
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createList(int arr[], int n) {
    if (n == 0) return NULL;

    struct Node *head = (struct Node*)malloc(sizeof(struct Node));
    head->data = arr[0];
    struct Node *current = head;

    for (int i = 1; i < n; i++) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}

void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Node* rotateRight(struct Node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    struct Node *tail = head;
    int length = 1;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    tail->next = head;

    k = k % length;

    int stepsToNewTail = length - k;
    struct Node *newTail = head;

    for (int i = 1; i < stepsToNewTail; i++) {
        newTail = newTail->next;
    }

    struct Node *newHead = newTail->next;

    newTail->next = NULL;

    return newHead;
}

int main() {
    int n, k;

    scanf("%d", &n);

    if (n <= 0) {
        return 0;
    }

    int *arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &k);

    struct Node *head = createList(arr, n);

    head = rotateRight(head, k);

    printList(head);

    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
    free(arr);

    return 0;
}