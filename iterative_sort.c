#include <stdio.h>

// Function to perform Bubble Sort iteratively
void bubbleSort(int arr[], size_t n)
{
    int swapped;
    for (size_t i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // If no two elements were swapped by inner loop, the array is sorted
        if (swapped == 0)
        {
            break;
        }
    }
}

// Function to perform iterative selection sort on an array of integers
void selectionSort(int arr[], size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; j++)
            if (arr[j] < arr[min_index])
                min_index = j;

        // Swap the found minimum element with the first element
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        int key = arr[i];
        size_t j = i - 1;

        // Move elements that are greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void merge(int arr[], size_t left_start, size_t mid, size_t right_end)
{
    size_t left_size = mid - left_start + 1;
    size_t right_size = right_end - mid;

    int *left_arr = (int *)malloc(left_size * sizeof(int));
    int *right_arr = (int *)malloc(right_size * sizeof(int));

    for (size_t i = 0; i < left_size; i++)
        left_arr[i] = arr[left_start + i];

    for (size_t i = 0; i < right_size; i++)
        right_arr[i] = arr[mid + 1 + i];

    size_t i = 0;
    size_t j = 0;
    size_t k = left_start;

    while (i < left_size && j < right_size)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < left_size)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    free(left_arr);
    free(right_arr);
}

void quickSort(int arr[], size_t n)
{
    // Create an auxiliary stack
    int *stack = (int *)malloc(n * sizeof(int));

    // Initialize top of stack
    int top = -1;

    // Push initial values of left and right to the stack
    stack[++top] = 0;
    stack[++top] = n - 1;

    // Keep popping from the stack while it's not empty
    while (top >= 0)
    {
        // Pop right and left
        int right = stack[top--];
        int left = stack[top--];

        // Set pivot element at its correct position
        // in the sorted array
        int pivot = partition(arr, left, right);

        // If there are elements on the left side of pivot,
        // then push left side to stack
        if (pivot - 1 > left)
        {
            stack[++top] = left;
            stack[++top] = pivot - 1;
        }

        // If there are elements on the right side of pivot,
        // then push right side to stack
        if (pivot + 1 < right)
        {
            stack[++top] = pivot + 1;
            stack[++top] = right;
        }
    }

    // Free the auxiliary stack
    free(stack);
}

// Function to partition the array into two segments
int partition(int arr[], int left, int right)
{
    int pivot = arr[right]; // Pivot element
    int i = left - 1;       // Index of smaller element

    for (int j = left; j <= right - 1; j++)
    {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot)
        {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }

    // Swap the pivot element with the element at index i+1
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

// Function to swap two elements in an array
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void countingSort(int arr[], size_t n) {
    // Find the maximum element to determine the range
    int max = arr[0];
    for (size_t i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Create an array to store count of each element
    int* count = (int*)malloc((max + 1) * sizeof(int));

    // Initialize count array to 0
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Store count of each element
    for (size_t i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Modify count array to store actual position of elements
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    int* output = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back to the original array
    for (size_t i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}