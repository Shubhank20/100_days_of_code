// Problem Statement:
// Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Tree.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 represents NULL)
// - Third line contains two node values

// Output Format:
// - Print the LCA value

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7
// 4 5

// Output:
// 2
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Structure for Queue used in Tree Construction
struct QueueNode {
    struct TreeNode *treeNode;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

// Queue Operations
void enqueue(struct Queue *q, struct TreeNode *tn) {
    struct QueueNode *temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    temp->treeNode = tn;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

struct TreeNode *dequeue(struct Queue *q) {
    if (q->front == NULL) return NULL;
    struct QueueNode *temp = q->front;
    struct TreeNode *tn = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return tn;
}

// Function to find the Lowest Common Ancestor
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, int p, int q) {
    if (root == NULL) {
        return NULL;
    }

    // If current node is one of the targets, return it
    if (root->val == p || root->val == q) {
        return root;
    }

    // Recurse on left and right subtrees
    struct TreeNode* leftLCA = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* rightLCA = lowestCommonAncestor(root->right, p, q);

    // If both sides returned a node, current root is the LCA
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }

    // Otherwise return the non-NULL value (or NULL if both are NULL)
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// Helper function to free memory
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    if (N == 0 || arr[0] == -1) {
        printf("Tree is empty\n");
        free(arr);
        return 0;
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = arr[0];
    root->left = root->right = NULL;

    struct Queue q = {NULL, NULL};
    enqueue(&q, root);

    int index = 1;
    while (index < N && q.front != NULL) {
        struct TreeNode* current = dequeue(&q);

        if (index < N && arr[index] != -1) {
            current->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            current->left->val = arr[index];
            current->left->left = current->left->right = NULL;
            enqueue(&q, current->left);
        }
        index++;

        if (index < N && arr[index] != -1) {
            current->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            current->right->val = arr[index];
            current->right->left = current->right->right = NULL;
            enqueue(&q, current->right);
        }
        index++;
    }

    int p, q_val;
    scanf("%d %d", &p, &q_val);

    struct TreeNode* lcaNode = lowestCommonAncestor(root, p, q_val);
    
    if (lcaNode != NULL) {
        printf("%d\n", lcaNode->val);
    } else {
        printf("NULL\n");
    }
    free(arr);
    freeTree(root);

    return 0;
}