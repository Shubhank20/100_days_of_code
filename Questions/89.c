// Problem Statement
// Given an array of integers where each element represents the number of pages in a book, and m students, allocate books such that each student gets at least one book and the maximum number of pages assigned to a student is minimized.

// Books must be allocated in contiguous order.

// Input Format
// n m
// n space-separated integers representing pages in books

// Output Format
// Print the minimum possible value of the maximum pages assigned to any student.

// Sample Input
// 4 2
// 12 34 67 90

// Sample Output
// 113

// Explanation
// One optimal allocation is:
// Student 1: 12 + 34 + 67 = 113
// Student 2: 90
// Maximum pages = 113 (minimum possible).
#include <stdio.h>
#include <limits.h>

// Function to check if it's possible to allocate books with a given max limit 'max_limit'
// Returns 1 if possible, 0 otherwise
int isPossible(int pages[], int n, int m, int max_limit) {
    int students_required = 1;
    int current_sum = 0;

    for (int i = 0; i < n; i++) {
        // If a single book has more pages than the limit, allocation is impossible
        // Note: The binary search logic ensures we start with max_limit >= max(pages),
        // so this check is technically redundant within the loop if setup is correct,
        // but good for safety.
        if (pages[i] > max_limit) {
            return 0;
        }

        if (current_sum + pages[i] > max_limit) {
            // Assign to next student
            students_required++;
            current_sum = pages[i];
            
            // If we need more students than available, this limit is too low
            if (students_required > m) {
                return 0;
            }
        } else {
            // Assign to current student
            current_sum += pages[i];
        }
    }
    return 1;
}

int main() {
    int n, m;
    
    // Read input
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    int pages[n];
    int sum = 0;
    int max_page = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
        sum += pages[i];
        if (pages[i] > max_page) {
            max_page = pages[i];
        }
    }

    // Binary search setup
    // Result will be between max_page (each student gets at least one book) and sum (one student gets all)
    int low = max_page;
    int high = sum;
    int result = sum; // Initialize with worst case

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isPossible(pages, n, m, mid)) {
            // 'mid' is a feasible solution, try to find a smaller one
            result = mid;
            high = mid - 1;
        } else {
            // 'mid' is not feasible, we need a larger limit
            low = mid + 1;
        }
    }

    printf("%d\n", result);

    return 0;
}