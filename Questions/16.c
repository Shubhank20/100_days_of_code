//Given an array of integers, count the frequency of each distinct element and print the result.

// Input:
// - First line: integer n (size of array)
// - Second line: n integers

// Output:
// - Print each element followed by its frequency in the format element:count

// Example:
// Input:
// 5
// 1 2 2 3 1

// Output:
// 1:2 2:2 3:1
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int freq[1001] = {0};
    int minVal = arr[0], maxVal = arr[0];
    
    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    
    for (int i = minVal; i <= maxVal; i++) {
        if (freq[i] > 0) {
            printf("%d:%d ", i, freq[i]);
        }
    }
    printf("\n");
    
    return 0;
}