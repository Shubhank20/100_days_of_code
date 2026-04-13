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

// Global variables for the hash table
int *hashTable;
int m; // Size of the hash table

// Hash function base h(k) = k % m
int hashFunc(int key) {
    return key % m;
}

// Quadratic Probing function: h(k, i) = (h(k) + i*i) % m
int quadraticProbe(int key, int i) {
    int h = hashFunc(key);
    return (h + (i * i)) % m;
}

// Function to insert a key into the hash table
void insert(int key) {
    for (int i = 0; i < m; i++) {
        int index = quadraticProbe(key, i);
        
        // If the slot is empty (-1) or contains the same key (update)
        if (hashTable[index] == -1 || hashTable[index] == key) {
            hashTable[index] = key;
            return;
        }
    }
    // If table is full and key not found (though problem implies valid inputs)
    printf("Table Full\n");
}

// Function to search for a key in the hash table
// Returns 1 if FOUND, 0 if NOT FOUND
int search(int key) {
    for (int i = 0; i < m; i++) {
        int index = quadraticProbe(key, i);
        
        if (hashTable[index] == key) {
            return 1; // FOUND
        }
        
        // If we hit an empty slot, the key is not in the table
        if (hashTable[index] == -1) {
            return 0; // NOT FOUND
        }
    }
    return 0; // Searched all possible slots and not found
}

int main() {
    int n;
    char op[10];
    int key;

    // Read the size of the hash table (m)
    if (scanf("%d", &m) != 1) return 0;

    // Read the number of operations (n)
    if (scanf("%d", &n) != 1) return 0;

    // Allocate memory for hash table and initialize to -1 (Empty)
    hashTable = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        hashTable[i] = -1;
    }

    // Process each operation
    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        
        if (strcmp(op, "INSERT") == 0) {
            scanf("%d", &key);
            insert(key);
        } else if (strcmp(op, "SEARCH") == 0) {
            scanf("%d", &key);
            if (search(key)) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
        }
    }

    // Free allocated memory
    free(hashTable);

    return 0;
}