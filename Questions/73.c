// Problem Statement
// Given a string s consisting of lowercase English letters, find and return the first character that does not repeat in the string. If all characters repeat, return '$'.

// Input Format
// A single string s.

// Output Format
// Print the first non-repeating character or '$' if none exists.

// Sample Input
// geeksforgeeks

// Sample Output
// f

// Explanation
// The character 'f' occurs only once in the string and appears before any other non-repeating character.
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10000

int main() {
    char s[MAX_SIZE];
    
    // Read the input string
    if (scanf("%s", s) != 1) {
        return 0;
    }

    int len = strlen(s);
    
    // Array to store frequency of each character (a-z)
    // Index 0 corresponds to 'a', 1 to 'b', etc.
    int count[26] = {0};

    // First Pass: Count frequency of each character
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }

    // Second Pass: Find the first character with frequency 1
    for (int i = 0; i < len; i++) {
        if (count[s[i] - 'a'] == 1) {
            printf("%c\n", s[i]);
            return 0;
        }
    }

    // If no non-repeating character is found
    printf("$\n");

    return 0;
}