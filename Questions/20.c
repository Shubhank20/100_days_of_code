// Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

// Input:
// - First line: integer n
// - Second line: n integers

// Output:
// - Print the count of subarrays having sum zero

// Example:
// Input:
// 6
// 1 -1 2 -2 3 -3

// Output:
// 6

// Explanation: A subarray is a continuous part of the array. For the input array 1 -1 2 -2 3 -3, the following subarrays have sum zero: [1, -1], [2, -2], [3, -3], [1, -1, 2, -2], [2, -2, 3, -3], and [1, -1, 2, -2, 3, -3]. Since there are 6 such subarrays, the output is 6.
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000005

long long countZeroSumSubarrays(int n, int* arr) {

    long long* map = (long long*)calloc(2 * 5 * MAX_SIZE + 5, sizeof(long long));
    if (map == NULL) {
        return -1;
    }

    long long count = 0;
    long long sum = 0;

    long long offset = n * 5; 

    map[0 + offset] = 1;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        count += map[sum + offset];

        map[sum + offset]++;
    }

    free(map);
    return count;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long result = countZeroSumSubarrays(n, arr);
    printf("%lld\n", result);

    free(arr);
    return 0;
}