// Problem Statement
// Given a string s consisting of lowercase letters, find the first repeated character in the string. A character is considered repeated if it appears more than once, and among all such characters, the one whose second occurrence has the smallest index should be returned.

// Input Format
// A single string s.

// Output Format
// Print the first repeated character. If no character is repeated, print -1.

// Sample Input
// geeksforgeeks

// Sample Output
// e
#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

int main() {
    char s[1000];
    
    // Read the input string
    if (scanf("%s", s) != 1) {
        return 0;
    }

    int len = strlen(s);
    
    // Array to store frequency of each character
    // Using a size of 256 to cover all standard ASCII characters
    int count[MAX_CHAR] = {0};

    // First Pass: Count frequency of each character
    for (int i = 0; i < len; i++) {
        count[(unsigned char)s[i]]++;
    }

    // Second Pass: Find the first character with frequency > 1
    for (int i = 0; i < len; i++) {
        if (count[(unsigned char)s[i]] > 1) {
            printf("%c\n", s[i]);
            return 0;
        }
    }

    // If no repeated character is found
    printf("-1\n");

    return 0;
}