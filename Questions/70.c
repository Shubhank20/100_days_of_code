// Problem Statement
// Implement a hash table using quadratic probing with formula:

// h(k, i) = (h(k) + i*i) % m

// Input Format
// Same as previous.

// Output Format
// Result of SEARCH operations.

// Sample Input
// 7
// 4
// INSERT 49
// INSERT 56
// SEARCH 49
// SEARCH 15

// Sample Output
// FOUND
// NOT FOUND

// Explanation
// Collisions resolved using i² jumps.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000 // Sufficiently large for the problem constraints

typedef struct {
    int key;
    int isOccupied;
} HashEntry;

HashEntry table[MAX_SIZE];

// Hash function h(k) = k % m
int hashFunc(int key, int m) {
    return key % m;
}

// Insert key into hash table
void insert(int key, int m) {
    int i = 0;
    int index;
    // Quadratic probing loop
    // We try up to m times to find an empty slot or the key itself
    while (i < m) {
        // Formula: h(k, i) = (h(k) + i*i) % m
        index = (hashFunc(key, m) + i * i) % m;

        if (!table[index].isOccupied) {
            // Found an empty slot
            table[index].key = key;
            table[index].isOccupied = 1;
            return;
        } else if (table[index].key == key) {
            // Key already exists, do nothing (or handle duplicate)
            return;
        }
        i++;
    }
    // If table is full (should not happen based on problem constraints usually)
    // printf("Table is full, cannot insert %d\n", key);
}

// Search key in hash table
void search(int key, int m) {
    int i = 0;
    int index;
    // We must probe exactly m times because quadratic probing
    // can visit less than m slots if m is not prime, but standard logic
    // dictates checking the cluster or the full cycle.
    while (i < m) {
        index = (hashFunc(key, m) + i * i) % m;

        if (table[index].isOccupied) {
            if (table[index].key == key) {
                printf("FOUND\n");
                return;
            }
        } else {
            // If we hit an empty slot, the key is definitely not in the table
            printf("NOT FOUND\n");
            return;
        }
        i++;
    }
    printf("NOT FOUND\n");
}

int main() {
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);

    // Initialize table
    for (int i = 0; i < MAX_SIZE; i++) {
        table[i].isOccupied = 0;
    }

    char operation[10];
    int key;

    for (int i = 0; i < n; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "INSERT") == 0) {
            scanf("%d", &key);
            insert(key, m);
        } else if (strcmp(operation, "SEARCH") == 0) {
            scanf("%d", &key);
            search(key, m);
        }
    }

    return 0;
}