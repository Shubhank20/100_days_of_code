// Problem: Convert an infix expression to postfix notation using stack.

// Input:
// - Single line: infix expression (operands are single characters)

// Output:
// - Print the postfix expression

// Example:
// Input:
// A+B*C

// Output:
// ABC*+

// Explanation:
// Operator precedence: * > +
// Use stack to handle operator precedence and associativity
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

void push(char item) {
    if (top >= MAX_SIZE - 1) {
        return;
    }
    stack[++top] = item;
}

char pop() {
    if (top < 0) {
        return -1;
    }
    return stack[top--];
}

int isOperator(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
        return 1;
    }
    return 0;
}

int precedence(char symbol) {
    if (symbol == '^') {
        return 3;
    } else if (symbol == '*' || symbol == '/') {
        return 2;
    } else if (symbol == '+' || symbol == '-') {
        return 1;
    }
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    int i, j = 0;
    char item, x;
    
    push('('); 
    strcat(infix, ")"); 
    
    item = infix[0];
    i = 0;
    
    while (item != '\0') {
        if (item == '(') {
            push(item);
        } else if (isdigit(item) || isalpha(item)) {
            postfix[j++] = item;
        } else if (isOperator(item)) {
            x = pop();
            while (isOperator(x) && precedence(x) >= precedence(item)) {
                postfix[j++] = x;
                x = pop();
            }
            push(x);
            push(item);
        } else if (item == ')') {
            x = pop();
            while (x != '(') {
                postfix[j++] = x;
                x = pop();
            }
        }
        i++;
        item = infix[i];
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    if (fgets(infix, MAX_SIZE, stdin) != NULL) {
        size_t len = strlen(infix);
        if (len > 0 && infix[len - 1] == '\n') {
            infix[len - 1] = '\0';
        }
    }

    infixToPostfix(infix, postfix);
    printf("%s\n", postfix);
    
    return 0;
}