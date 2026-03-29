// Problem Statement:
// Convert a binary tree into its mirror image by swapping left and right children at every node.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 indicates NULL)

// Output Format:
// - Print inorder traversal of mirrored tree

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7

// Output:
// 7 3 6 1 5 2 4

// Explanation:
// Each node’s left and right children are swapped recursively.
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
newNode->val = val;
newNode->left = NULL;
newNode->right = NULL;
return newNode;
}

struct TreeNode* buildTree(int N, int* arr) {
if (N == 0 || arr[0] == -1) return NULL;

struct TreeNode* root = createNode(arr[0]);

struct TreeNode** queue = (struct TreeNode**)malloc(N * sizeof(struct TreeNode*));
int front = 0, rear = 0;
queue[rear++] = root;

int i = 1;
while (front < rear && i < N) {
struct TreeNode* current = queue[front++];

if (i < N && arr[i] != -1) {
current->left = createNode(arr[i]);
queue[rear++] = current->left;
}
i++;

if (i < N && arr[i] != -1) {
current->right = createNode(arr[i]);
queue[rear++] = current->right;
}
i++;
}

free(queue);
return root;
}

void mirrorTree(struct TreeNode* root) {
if (root == NULL) return;

mirrorTree(root->left);
mirrorTree(root->right);

struct TreeNode* temp = root->left;
root->left = root->right;
root->right = temp;
}

void printInorder(struct TreeNode* root) {
if (root == NULL) return;

printInorder(root->left);
printf("%d ", root->val);
printInorder(root->right);
}

int main() {
int N;
scanf("%d", &N);

if (N <= 0) {
return 0;
}

int* arr = (int*)malloc(N * sizeof(int));
for (int i = 0; i < N; i++) {
scanf("%d", &arr[i]);
}

struct TreeNode* root = buildTree(N, arr);

mirrorTree(root);

printInorder(root);
printf("\n");

free(arr);

return 0;
}