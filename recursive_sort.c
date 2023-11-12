#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to perform Bubble Sort recursively
void recursiveBubbleSort(int arr[], int n)
{
    // Base case: If there is only one element or the array is empty
    if (n <= 1)
        return;

    // One pass of bubble sort: Move the largest element to the end
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
        {
            // Swap arr[i] and arr[i+1]
            arr[i] = arr[i] + arr[i + 1] - (arr[i + 1] = arr[i]);
        }

    // Recursively sort the remaining elements
    recursiveBubbleSort(arr, n - 1);
}

void findMinAndSwap(int arr[], int n, int i)
{
    int min_index = i;

    // Find the index of the minimum element in the unsorted part of the array
    for (int j = i + 1; j < n; j++)
        if (arr[j] < arr[min_index])
            min_index = j;

    // Swap the found minimum element with the first element
    arr[i] = arr[i] + arr[min_index] - (arr[min_index] = arr[i]);
}

// Function to perform recursive selection sort on an array of integers
void recursiveSelectionSort(int arr[], int n, int i)
{
    if (i < n - 1)
    {
        // Find the minimum element in the unsorted part and swap with the first element
        findMinAndSwap(arr, n, i);

        // Recursively sort the rest of the array
        recursiveSelectionSort(arr, n, i + 1);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;   // Initial index of first subarray
    j = 0;   // Initial index of second subarray
    k = l;   // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void recursiveMergeSort(int arr[], int left_start, int right_end)
{
    if (left_start < right_end)
    {
        int mid = left_start + (right_end - left_start) / 2;
        recursiveMergeSort(arr, left_start, mid);
        recursiveMergeSort(arr, mid + 1, right_end);
        merge(arr, left_start, mid, right_end);
    }
}

int optimizedPartition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
        {
            i++;
            arr[i] = arr[i] + arr[j] - (arr[j] = arr[i]);
        }

    arr[i + 1] = arr[i + 1] + arr[high] - (arr[high] = arr[i + 1]);

    return i + 1;
}

void recursiveQuickSort(int arr[], int low, int high)
{
    while (low < high)
    {
        int pi = optimizedPartition(arr, low, high);

        if (pi - low < high - pi)
        {
            recursiveQuickSort(arr, low, pi - 1);
            low = pi + 1;
        }
        else
        {
            recursiveQuickSort(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        // Swap arr[i] and arr[largest]
        arr[i] = arr[i] + arr[largest] - (arr[largest] = arr[i]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void recursiveHeapSort(int arr[], int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--)
    {
        // Swap the root (maximum element) with the last element
        arr[0] = arr[0] + arr[i] - (arr[i] = arr[0]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int getMaxi(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

void countSort(int arr[], int n, int exp)
{
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void recursiveRadixSort(int arr[], int n)
{
    int max = getMaxi(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void swaper(int *a, int *b)
{
    *a = *a + *b - (*b = *a);
}

void recursiveBitonicMerge(int arr[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
        {
            if (dir == (arr[i] > arr[i + k]))
            {
                swaper(&arr[i], &arr[i + k]);
            }
        }
        recursiveBitonicMerge(arr, low, k, dir);
        recursiveBitonicMerge(arr, low + k, k, dir);
    }
}

void recursiveBitonicSorter(int arr[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        // Sort in ascending order
        recursiveBitonicSorter(arr, low, k, 1);

        // Sort in descending order
        recursiveBitonicSorter(arr, low + k, k, 0);

        // Merge the entire sequence
        recursiveBitonicMerge(arr, low, cnt, dir);
    }
}

void recursiveBitonicSort(int arr[], int n)
{
    recursiveBitonicSorter(arr, 0, n, 1);
}

void flip(int arr[], int i)
{
    int start = 0;
    while (start < i)
    {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int findMaxIndex(int arr[], int n)
{
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

void recursivePancakeSort(int arr[], int n)
{
    for (int curr_size = n; curr_size > 1; --curr_size)
    {
        int mi = findMaxIndex(arr, curr_size);

        if (mi != curr_size - 1)
        {
            flip(arr, mi);
            flip(arr, curr_size - 1);
        }
    }
}

int isSorted(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;

    return 1;
}

void shuffle(int arr[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void recursiveBogoSort(int arr[], int n)
{
    srand(time(NULL));

    while (!isSorted(arr, n))
        shuffle(arr, n);
}

void recursiveStoogeSorter(int arr[], int low, int high)
{
    if (low >= high)
        return;

    if (arr[low] > arr[high])
        swaper(&arr[low], &arr[high]);

    if (high - low + 1 > 2)
    {
        int t = (high - low + 1) / 3;
        recursiveStoogeSorter(arr, low, high - t);
        recursiveStoogeSorter(arr, low + t, high);
        recursiveStoogeSorter(arr, low, high - t);
    }
}

void recursiveStoogeSort(int arr[], int n)
{
    recursiveStoogeSorter(arr, 0, n - 1);
}

/*void recursiveSleepSort(int arr[], int n) {
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