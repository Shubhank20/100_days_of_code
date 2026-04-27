// Problem: Find the integer square root of a given non-negative integer using Binary Search. The integer square root of a number is defined as the greatest integer whose square is less than or equal to the given number.

// Input:
// - First line: an integer n

// Output:
// - Print the integer square root of n

// Examples:
// Input:
// 64

// Output:
// 8

// Input:
// 20

// Output:
// 4

// Input:
// 1

// Output:
// 1

// Explanation:
// Binary Search is applied on the range 0 to n. At each step, the middle value is squared and compared with n. If mid * mid equals n, mid is the square root. If mid * mid is less than n, search continues in the right half; otherwise, in the left half. The final answer is the largest integer whose square does not exceed n.
#include <stdio.h>

int integerSqrt(int n) {
    if (n == 0 || n == 1) {
        return n;
    }

    int start = 1;
    int end = n;
    int result = 0;

    while (start <= end) {
        // Calculate mid to avoid potential overflow compared to (start+end)/2
        int mid = start + (end - start) / 2;

        // Use long long to prevent overflow when squaring mid
        // since mid * mid might exceed the range of a standard integer
        long long square = (long long)mid * mid;

        if (square == n) {
            return mid;
        }

        if (square < n) {
            // If mid^2 is less than n, mid is a potential candidate.
            // We store it and search for a larger value in the right half.
            result = mid;
            start = mid + 1;
        } else {
            // If mid^2 is greater than n, the answer must be in the left half.
            end = mid - 1;
        }
    }

    return result;
}

int main() {
    int n;
    
    // Read the input integer
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Compute and print the integer square root
    printf("%d\n", integerSqrt(n));

    return 0;
}