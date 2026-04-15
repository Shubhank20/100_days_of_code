// Problem Statement
// Given an array of candidate names where each name represents a vote cast for that candidate, determine the candidate who received the maximum number of votes. In case of a tie, return the lexicographically smallest candidate name.

// Input Format
// First line contains an integer n representing number of votes.
// Second line contains n space-separated strings representing candidate names.

// Output Format
// Print the name of the winning candidate followed by the number of votes received.

// Sample Input
// 13
// john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john

// Sample Output
// john 4

// Explanation
// Both john and johnny receive 4 votes, but john is lexicographically smaller, so john is declared the winner.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparator function for qsort to sort strings in lexicographical order
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int n;
    // Read the number of votes
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Allocate memory for the array of strings (names)
    char **votes = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        votes[i] = (char *)malloc(101 * sizeof(char)); // Assuming max name length is 100
    }

    // Read the names
    for (int i = 0; i < n; i++) {
        scanf("%s", votes[i]);
    }

    // Sort the names lexicographically
    qsort(votes, n, sizeof(char *), compareStrings);

    char *winner = votes[0];
    int maxVotes = 1;
    int currentCount = 1;

    // Iterate through the sorted array to count votes
    for (int i = 1; i < n; i++) {
        // Compare current name with previous name
        if (strcmp(votes[i], votes[i - 1]) == 0) {
            currentCount++;
        } else {
            // Check if the previous candidate is the new winner
            // Condition 1: Strictly more votes
            // Condition 2: Same votes but lexicographically smaller name
            if (currentCount > maxVotes || 
               (currentCount == maxVotes && strcmp(votes[i - 1], winner) < 0)) {
                maxVotes = currentCount;
                winner = votes[i - 1];
            }
            // Reset count for the new candidate
            currentCount = 1;
        }
    }

    // Handle the last candidate group
    if (currentCount > maxVotes || 
       (currentCount == maxVotes && strcmp(votes[n - 1], winner) < 0)) {
        maxVotes = currentCount;
        winner = votes[n - 1];
    }

    // Output the result
    printf("%s %d\n", winner, maxVotes);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(votes[i]);
    }
    free(votes);

    return 0;
}