// Problem Statement
// Given an array of integers containing both positive and negative values, find the length of the longest contiguous subarray whose sum is equal to zero.

// Input Format
// An integer array arr[].

// Output Format
// Print the length of the longest subarray with sum equal to zero.

// Sample Input
// 15 -2 2 -8 1 7 10 23

// Sample Output
// 5

// Explanation
// The subarray [-2, 2, -8, 1, 7] has a sum of 0 and is the longest such subarray.
#include <stdio.h>
#include <stdlib.h>

// A structure to represent a hash entry for storing sum and index
typedef struct {
    long long key;
    int value;
} HashEntry;

// A structure to represent the Hash Map
typedef struct {
    int size;
    HashEntry* entries;
} HashMap;

// Create a new Hash Map
HashMap* createHashMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->entries = (HashEntry*)calloc(size, sizeof(HashEntry));
    // Initialize keys to a value that won't appear naturally
    for(int i = 0; i < size; i++) {
        map->entries[i].key = -99999999999; 
    }
    return map;
}

// Simple Hash Function
int hashCode(HashMap* map, long long key) {
    if (key < 0) key = -key;
    return (int)(key % map->size);
}

// Put a key-value pair into the Hash Map
void put(HashMap* map, long long key, int value) {
    int index = hashCode(map, key);
    
    // Linear probing to handle collisions
    while (map->entries[index].key != -99999999999) {
        if (map->entries[index].key == key) {
            return; // Key already exists, don't update index because we want the first occurrence
        }
        index = (index + 1) % map->size;
    }
    map->entries[index].key = key;
    map->entries[index].value = value;
}

// Get the value for a key from the Hash Map, returns -1 if not found
int get(HashMap* map, long long key) {
    int index = hashCode(map, key);
    
    while (map->entries[index].key != -99999999999) {
        if (map->entries[index].key == key) {
            return map->entries[index].value;
        }
        index = (index + 1) % map->size;
    }
    return -1;
}

void freeHashMap(HashMap* map) {
    free(map->entries);
    free(map);
}

int maxLen(int arr[], int n) {
    HashMap* map = createHashMap(2 * n + 1); // Size to reduce collisions
    long long sum = 0;
    int max_len = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        // If the current sum is 0, the subarray from start to i sums to 0
        if (sum == 0) {
            max_len = i + 1;
        }

        // If this sum has been seen before
        int prevIndex = get(map, sum);
        if (prevIndex != -1) {
            // Update max_len if current subarray is longer
            if (i - prevIndex > max_len) {
                max_len = i - prevIndex;
            }
        } else {
            // Store the first occurrence of this sum
            put(map, sum, i);
        }
    }

    freeHashMap(map);
    return max_len;
}

int main() {
    // Note: Since standard C input reading for arrays of arbitrary size is verbose, 
    // this example assumes the input array is hardcoded or parsed from a string.
    // For the purpose of the problem statement, here is the logic using the sample.
    
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", maxLen(arr, n));

    return 0;
}