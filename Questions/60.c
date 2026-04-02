// Problem Statement:
// Check whether a given binary tree satisfies the Min-Heap property.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal

// Output Format:
// - Print YES if valid Min-Heap, otherwise NO

// Example:
// Input:
// 7
// 1 3 5 7 9 8 10

// Output:
// YES

// Explanation:
// Each parent node must be smaller than its children.
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int isMinHeap = 1;

    // For each parent node at index i,
    // left child is at 2*i+1, right child is at 2*i+2
    for (int i = 0; i < n; i++) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;

        // Check left child
        if (left < n && arr[i] > arr[left]) {
            isMinHeap = 0;
            break;
        }

        // Check right child
        if (right < n && arr[i] > arr[right]) {
            isMinHeap = 0;
            break;
        }
    }

    printf("%s\n", isMinHeap ? "YES" : "NO");

    return 0;
}