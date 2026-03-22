// Problem: BST Search

// Implement the solution for this problem.

// Input:
// - Input specifications

// Output:
// - Output specifications
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    while (root != NULL) {
        if (root->val == val) {
            return root;
        }
        
        if (val < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return NULL;
}

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printTree(struct TreeNode* root) {
    if (root == NULL) {
        printf("null ");
        return;
    }
    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

int main() {
    struct TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(1);
    root->left->right = createNode(3);

    int valToFind = 2;
    
    printf("Tree (Pre-order): ");
    printTree(root);
    printf("\nSearching for value: %d\n", valToFind);

    struct TreeNode* result = searchBST(root, valToFind);

    if (result != NULL) {
        printf("Found Subtree (Pre-order): ");
        printTree(result);
        printf("\n");
    } else {
        printf("Value not found.\n");
    }

    valToFind = 5;
    printf("\nSearching for value: %d\n", valToFind);
    result = searchBST(root, valToFind);
    
    if (result != NULL) {
        printTree(result);
    } else {
        printf("Value not found.\n");
    }

    return 0;
}