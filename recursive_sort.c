#include <stdio.h>

// Function to perform Bubble Sort recursively
void recursiveBubbleSort(int arr[], int n)
{
    // Base case: If there is only one element or the array is empty
    if (n <= 1)
    {
        return;
    }

    // One pass of bubble sort: Move the largest element to the end
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            // Swap arr[i] and arr[i+1]
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }

    // Recursively sort the remaining elements
    recursiveBubbleSort(arr, n - 1);
}

void findMinAndSwap(int arr[], size_t n, size_t i)
{
    size_t min_index = i;

    // Find the index of the minimum element in the unsorted part of the array
    for (size_t j = i + 1; j < n; j++)
    {
        if (arr[j] < arr[min_index])
        {
            min_index = j;
        }
    }

    // Swap the found minimum element with the first element
    int temp = arr[i];
    arr[i] = arr[min_index];
    arr[min_index] = temp;
}

// Function to perform recursive selection sort on an array of integers
void recursiveSelectionSort(int arr[], size_t n, size_t i)
{
    if (i < n - 1)
    {
        // Find the minimum element in the unsorted part and swap with the first element
        findMinAndSwap(arr, n, i);

        // Recursively sort the rest of the array
        recursiveSelectionSort(arr, n, i + 1);
    }
}

void recursiveMergeSort(int arr[], size_t left_start, size_t right_end)
{
    if (left_start < right_end)
    {
        size_t mid = left_start + (right_end - left_start) / 2;
        optimizedMergeSort(arr, left_start, mid);
        optimizedMergeSort(arr, mid + 1, right_end);
        merge(arr, left_start, mid, right_end);
    }
}

size_t optimizedPartition(int arr[], size_t low, size_t high)
{
    int pivot = arr[high];
    size_t i = low - 1;

    for (size_t j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void recursiveQuickSort(int arr[], size_t low, size_t high)
{
    while (low < high)
    {
        size_t pi = optimizedPartition(arr, low, high);

        if (pi - low < high - pi)
        {
            optimizedQuickSort(arr, low, pi - 1);
            low = pi + 1;
        }
        else
        {
            optimizedQuickSort(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}