// Problem Statement:
// Construct a binary tree from given preorder and inorder traversal arrays.

// Input Format:
// - First line contains integer N
// - Second line contains preorder traversal
// - Third line contains inorder traversal

// Output Format:
// - Print postorder traversal of constructed tree

// Example:
// Input:
// 5
// 1 2 4 5 3
// 4 2 5 1 3

// Output:
// 4 5 2 3 1

// Explanation:
// Preorder identifies root, inorder splits left and right subtrees
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* buildTreeHelper(int* preorder, int preStart, int preEnd, 
                                 int* inorder, int inStart, int inEnd, 
                                 int* inorderMap) {
    if (preStart > preEnd || inStart > inEnd) {
        return NULL;
    }
    
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[preStart];
    root->left = NULL;
    root->right = NULL;
    
    int rootPos = inorderMap[root->val + 3000];
    int leftSubtreeSize = rootPos - inStart;
    
    root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSubtreeSize,
                                inorder, inStart, rootPos - 1, inorderMap);
    
    root->right = buildTreeHelper(preorder, preStart + leftSubtreeSize + 1, preEnd,
                                 inorder, rootPos + 1, inEnd, inorderMap);
    
    return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int* inorderMap = (int*)malloc(6001 * sizeof(int));
    memset(inorderMap, -1, 6001 * sizeof(int));
    
    for (int i = 0; i < inorderSize; i++) {
        inorderMap[inorder[i] + 3000] = i;
    }
    
    struct TreeNode* root = buildTreeHelper(preorder, 0, preorderSize - 1,
                                          inorder, 0, inorderSize - 1,
                                          inorderMap);
    
    free(inorderMap);
    return root;
}

void printPostorder(struct TreeNode* node) {
    if (node == NULL)
        return;

    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->val);
}

void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int N;

    if (scanf("%d", &N) != 1) {
        return 0;
    }

    int* preorder = (int*)malloc(N * sizeof(int));
    int* inorder = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &preorder[i]);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &inorder[i]);
    }

    struct TreeNode* root = buildTree(preorder, N, inorder, N);

    printPostorder(root);
    printf("\n");

    freeTree(root);
    free(preorder);
    free(inorder);

    return 0;
}