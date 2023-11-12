#include <stdio.h>

// Function to perform Bubble Sort iteratively
void iterativeBubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform iterative selection sort on an array of integers
void selectionSort(int arr[], size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_index = i;

        // Find the index of the minimum element in the unsorted part of the array
        for (size_t j = i + 1; j < n; j++)
            if (arr[j] < arr[min_index])
                min_index = j;

        // Swap the found minimum element with the first element
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}