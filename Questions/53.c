// Problem Statement:
// Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

// Input Format:
// - First line contains integer N (number of nodes)
// - Second line contains N space-separated integers representing level-order traversal (-1 indicates NULL)

// Output Format:
// - Print nodes column by column from leftmost to rightmost vertical line

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7

// Output:
// 4
// 2
// 1 5 6
// 3
// 7

// Explanation:
// Vertical lines are formed based on horizontal distance from root. Nodes sharing the same distance are printed together.
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct HashNode {
    int key;          
    ListNode *head;   
    struct HashNode *next;
} HashNode;

typedef struct QNode {
    TreeNode *treeNode;
    int hd;             
    struct QNode *next;
} QNode;

typedef struct Queue {
    QNode *front, *rear;
} Queue;

#define HASH_SIZE 10007 

HashNode* hashTable[HASH_SIZE];

void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int getHash(int key) {
    if (key < 0) key = -key;
    return key % HASH_SIZE;
}

void addToHash(int key, int value) {
    int index = getHash(key);
    HashNode *hNode = hashTable[index];

    while (hNode != NULL) {
        if (hNode->key == key) {
            ListNode *newLNode = (ListNode*)malloc(sizeof(ListNode));
            newLNode->data = value;
            newLNode->next = NULL;
            
            ListNode *temp = hNode->head;
            if (temp == NULL) {
                hNode->head = newLNode;
            } else {
                while (temp->next != NULL) temp = temp->next;
                temp->next = newLNode;
            }
            return;
        }
        hNode = hNode->next;
    }
    HashNode *newHNode = (HashNode*)malloc(sizeof(HashNode));
    newHNode->key = key;
    
    ListNode *newLNode = (ListNode*)malloc(sizeof(ListNode));
    newLNode->data = value;
    newLNode->next = NULL;
    
    newHNode->head = newLNode;
    newHNode->next = hashTable[index];
    hashTable[index] = newHNode;
}
Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tn, int hd) {
    QNode *temp = (QNode*)malloc(sizeof(QNode));
    temp->treeNode = tn;
    temp->hd = hd;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

void dequeue(Queue *q, TreeNode **tn, int *hd) {
    if (q->front == NULL) return;
    QNode *temp = q->front;
    *tn = temp->treeNode;
    *hd = temp->hd;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}
TreeNode* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = arr[0];
    root->left = root->right = NULL;

    Queue *q = createQueue();
    enqueue(q, root, 0); 

    int i = 1;
    while (!isEmpty(q) && i < n) {
        TreeNode *current;
        int temp;
        dequeue(q, &current, &temp);

        if (i < n && arr[i] != -1) {
            current->left = (TreeNode*)malloc(sizeof(TreeNode));
            current->left->data = arr[i];
            current->left->left = current->left->right = NULL;
            enqueue(q, current->left, 0);
        }
        i++;

        if (i < n && arr[i] != -1) {
            current->right = (TreeNode*)malloc(sizeof(TreeNode));
            current->right->data = arr[i];
            current->right->left = current->right->right = NULL;
            enqueue(q, current->right, 0);
        }
        i++;
    }
    return root;
}

int hds[2000];
int hdCount = 0;

void verticalOrderTraversal(TreeNode *root) {
    if (root == NULL) return;

    initHashTable();
    Queue *q = createQueue();

    enqueue(q, root, 0);

    while (!isEmpty(q)) {
        TreeNode *currNode;
        int currHD;
        dequeue(q, &currNode, &currHD);

        addToHash(currHD, currNode->data);

        int found = 0;
        for(int k=0; k<hdCount; k++) {
            if(hds[k] == currHD) { found = 1; break; }
        }
        if(!found) {
            hds[hdCount++] = currHD;
        }

        // Enqueue children
        if (currNode->left != NULL) {
            enqueue(q, currNode->left, currHD - 1);
        }
        if (currNode->right != NULL) {
            enqueue(q, currNode->right, currHD + 1);
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    TreeNode *root = buildTree(arr, n);
    
    verticalOrderTraversal(root);

    qsort(hds, hdCount, sizeof(int), compare);

    for (int i = 0; i < hdCount; i++) {
        int key = hds[i];
        int index = getHash(key);
        HashNode *hNode = hashTable[index];

        while (hNode != NULL) {
            if (hNode->key == key) {
                ListNode *lNode = hNode->head;
                while (lNode != NULL) {
                    printf("%d ", lNode->data);
                    lNode = lNode->next;
                }
                printf("\n");
                break;
            }
            hNode = hNode->next;
        }
    }

    return 0;
}