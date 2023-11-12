#include <stdio.h>

// Function to perform Bubble Sort recursively
void recursiveBubbleSort(int arr[], int n) {
    // Base case: If there is only one element or the array is empty
    if (n <= 1) {
        return;
    }

    // One pass of bubble sort: Move the largest element to the end
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            // Swap arr[i] and arr[i+1]
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }

    // Recursively sort the remaining elements
    recursiveBubbleSort(arr, n - 1);
}