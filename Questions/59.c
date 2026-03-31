// Problem Statement:
// Construct a binary tree from given inorder and postorder traversal arrays.

// Input Format:
// - First line contains integer N
// - Second line contains inorder traversal
// - Third line contains postorder traversal

// Output Format:
// - Print preorder traversal of constructed tree

// Example:
// Input:
// 5
// 4 2 5 1 3
// 4 5 2 3 1

// Output:
// 1 2 4 5 3

// Explanation:
// Postorder gives root at end, inorder divides left and right subtrees.
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* buildTreeHelper(int* inorder, int inStart, int inEnd, 
                                int* postorder, int postStart, int postEnd) {
    if (inStart > inEnd) {
        return NULL;
    }
    
    int rootValue = postorder[postEnd];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootValue;
    root->left = NULL;
    root->right = NULL;
    
    int rootIndex = 0;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == rootValue) {
            rootIndex = i;
            break;
        }
    }
    
    int leftNodes = rootIndex - inStart;
    
    root->left = buildTreeHelper(inorder, inStart, rootIndex - 1, 
                                postorder, postStart, postStart + leftNodes - 1);
    root->right = buildTreeHelper(inorder, rootIndex + 1, inEnd, 
                                 postorder, postStart + leftNodes, postEnd - 1);
    
    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    return buildTreeHelper(inorder, 0, inorderSize - 1, 
                          postorder, 0, postorderSize - 1);
}

void printPreorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    
    int* inorder = (int*)malloc(n * sizeof(int));
    int* postorder = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }
    
    struct TreeNode* root = buildTree(inorder, n, postorder, n);
    
    printPreorder(root);
    printf("\n");
    
    free(inorder);
    free(postorder);
    
    return 0;
}