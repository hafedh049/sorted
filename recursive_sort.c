#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


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

void heapify(int arr[], size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        // Swap arr[i] and arr[largest]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void recursiveHeapSort(int arr[], size_t n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Swap the root (maximum element) with the last element
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int getMax(int arr[], size_t n) {
    int max = arr[0];
    for (size_t i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    
    return max;
}

void countSort(int arr[], size_t n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};

    for (size_t i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (size_t i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void recursiveRadixSort(int arr[], size_t n) {
    int max = getMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void recursiveBitonicMerge(int arr[], size_t low, size_t cnt, int dir) {
    if (cnt > 1) {
        size_t k = cnt / 2;
        for (size_t i = low; i < low + k; i++) {
            if (dir == (arr[i] > arr[i + k])) {
                swap(&arr[i], &arr[i + k]);
            }
        }
        recursiveBitonicMerge(arr, low, k, dir);
        recursiveBitonicMerge(arr, low + k, k, dir);
    }
}

void recursiveBitonicSorter(int arr[], size_t low, size_t cnt, int dir) {
    if (cnt > 1) {
        size_t k = cnt / 2;

        // Sort in ascending order
        recursiveBitonicSorter(arr, low, k, 1);

        // Sort in descending order
        recursiveBitonicSorter(arr, low + k, k, 0);

        // Merge the entire sequence
        recursiveBitonicMerge(arr, low, cnt, dir);
    }
}

void recursiveBitonicSort(int arr[], size_t n) {
    bitonicSorter(arr, 0, n, 1);
}

void flip(int arr[], size_t i) {
    size_t start = 0;
    while (start < i) {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

size_t findMaxIndex(int arr[], size_t n) {
    size_t mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

void recursivePancakeSort(int arr[], size_t n) {
    for (size_t curr_size = n; curr_size > 1; --curr_size) {
        size_t mi = findMaxIndex(arr, curr_size);

        if (mi != curr_size - 1) {
            flip(arr, mi);
            flip(arr, curr_size - 1);
        }
    }
}

int isSorted(int arr[], size_t n) {
    for (size_t i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;

    return 1;
}

void shuffle(int arr[], size_t n) {
    for (size_t i = n - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void recursiveBogoSort(int arr[], size_t n) {
    srand(time(NULL));

    while (!isSorted(arr, n))
        shuffle(arr, n);
}

void recursiveStoogeSorter(int arr[], size_t low, size_t high) {
    if (low >= high)
        return;

    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);

    if (high - low + 1 > 2) {
        size_t t = (high - low + 1) / 3;
        recursiveStoogeSorter(arr, low, high - t);
        recursiveStoogeSorter(arr, low + t, high);
        recursiveStoogeSorter(arr, low, high - t);
    }
}

void recursiveStoogeSort(int arr[], size_t n) {
    recursiveStoogeSorter(arr, 0, n - 1);
}

/*void recursiveSleepSort(int arr[], size_t n) {
    if (n == 0)
        return;

    // Create a thread to sleep for the value of the first element
    pthread_t thread;
    pthread_create(&thread, NULL, (void *(*)(void *))sleep, (void *)(intptr_t)arr[0]);

    // Sort the remaining elements using recursion
    sleepSortRecursive(arr + 1, n - 1);

    // Wait for the thread to finish
    pthread_join(thread, NULL);
}*/