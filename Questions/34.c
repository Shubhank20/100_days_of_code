// Problem: Evaluate Postfix Expression - Implement using linked list with dynamic memory allocation.

// Input:
// - Postfix expression with operands and operators

// Output:
// - Print the integer result

// Example:
// Input:
// 2 3 1 * + 9 -

// Output:
// -4

// Explanation:
// Use stack to store operands, apply operators by popping operands, push result back. Final stack top is result.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct Node** top, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

// Pop operation
int pop(struct Node** top) {
    if (*top == NULL) {
        return 0;
    }
    struct Node* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

int isOperator(const char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

// Function to perform operation
int performOperation(int a, int b, const char* op) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) return a / b;
    return 0;
}

int main() {
    char input[1000];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    struct Node* stack = NULL;
    char* token = strtok(input, " \n");

    while (token != NULL) {
        if (isOperator(token)) {
            int val2 = pop(&stack);
            int val1 = pop(&stack);
            int result = performOperation(val1, val2, token);
            push(&stack, result);
        } else {
            push(&stack, atoi(token));
        }
        token = strtok(NULL, " \n");
    }
    if (stack != NULL) {
        printf("%d\n", stack->data);
        free(stack);
    }

    return 0;
}