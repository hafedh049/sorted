#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "print.c"

#define MIN_MERGE 32

// Function to perform Bubble Sort iteratively
void bubbleSort(int arr[], int n)
{
    toString(arr, n);
    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j+1]
                arr[j] = arr[j] + arr[j + 1] - (arr[j + 1] = arr[j]);
                swapped = 1;
            }
        // If no two elements were swapped by inner loop, the array is sorted
        if (swapped == 0)
            break;
    }
    toString(arr, n);
}

// Function to perform iterative selection sort on an array of integers
void selectionSort(int arr[], int n)
{
    toString(arr, n);
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_index])
                min_index = j;

        // Swap the found minimum element with the first element
        arr[min_index] = arr[min_index] + arr[i] - (arr[i] = arr[min_index]);
    }
    toString(arr, n);
}

void insertionSort(int arr[], int n)
{
    toString(arr, n);
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    toString(arr, n);
}

void bucketSort(int arr[], int n)
{
    toString(arr, n);
    int max = arr[0];
    int min = arr[0];

    // Find the maximum and minimum values in the array
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];

        if (arr[i] < min)
            min = arr[i];
    }

    // Calculate the range of each bucket
    int range = (max - min) / n + 1;

    // Create an array of buckets
    int **buckets = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    // Initialize each bucket
    for (int i = 0; i < n; i++)
        buckets[i][0] = 0; // Bucket size

    // Distribute elements into buckets
    for (int i = 0; i < n; i++)
    {
        int index = (arr[i] - min) / range;
        int size = ++buckets[index][0];
        buckets[index][size] = arr[i];
    }

    // Sort each bucket and update the original array
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        int size = buckets[i][0];
        if (size > 0)
        {
            insertionSort(buckets[i] + 1, size);
            for (int j = 1; j <= size; j++)
                arr[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    free(buckets);
    toString(arr, n);
}

void shellSort(int arr[], int n)
{
    toString(arr, n);
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    toString(arr, n);
}

void merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    toString(arr, right - left + 1);

    if (left < right)
    {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
    toString(arr, right - left + 1);
}

void insertionSorted(int arr[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void timSort(int arr[], int n)
{
    toString(arr, n);
    for (int i = 0; i < n; i += MIN_MERGE)
    {
        int left = i;
        int right = (i + MIN_MERGE - 1 < n - 1) ? (i + MIN_MERGE - 1) : (n - 1);
        insertionSorted(arr, left, right);
    }

    for (int size = MIN_MERGE; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);
            merge(arr, left, mid, right);
        }
    }
    toString(arr, n);
}

// Function to swap two elements in an array
void swap(int *a, int *b)
{
    *a = *a + *b - (*b = *a);
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

void quickSort(int arr[], int n)
{
    toString(arr, n);
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
    toString(arr, n);
}

int getNextGap(int gap)
{
    // Shrink gap by a factor of 1.3
    gap = (gap * 10) / 13;

    return (gap < 1) ? 1 : gap;
}

void combSort(int arr[], int n)
{
    toString(arr, n);
    int gap = n;

    bool swapped = true;

    while (gap != 1 || swapped)
    {
        gap = getNextGap(gap);

        swapped = false;

        for (int i = 0; i < n - gap; i++)
            if (arr[i] > arr[i + gap])
            {
                swap(&arr[i], &arr[i + gap]);
                swapped = true;
            }
    }
    toString(arr, n);
}

void pigeonholeSort(int arr[], int n)
{
    toString(arr, n);
    int min = arr[0];
    int max = arr[0];

    // Find the minimum and maximum values in the array
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];

        if (arr[i] > max)
            max = arr[i];
    }

    int range = max - min + 1;
    int *pigeonholes = (int *)malloc(range * sizeof(int));

    // Initialize pigeonholes
    for (int i = 0; i < range; i++)
        pigeonholes[i] = 0;

    // Count occurrences of each element in the array
    for (int i = 0; i < n; i++)
        pigeonholes[arr[i] - min]++;

    // Fill the original array with sorted values
    int index = 0;
    for (int i = 0; i < range; i++)
        while (pigeonholes[i] > 0)
        {
            arr[index++] = i + min;
            pigeonholes[i]--;
        }

    free(pigeonholes);
    toString(arr, n);
}

void cocktailShakerSort(int arr[], int n)
{
    toString(arr, n);
    int swapped;

    do
    {
        // Perform a forward pass
        swapped = 0;
        for (int i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }

        if (!swapped)
            break; // If no swapping occurred, the array is sorted

        // Perform a backward pass
        swapped = 0;
        for (int i = n - 1; i > 0; i--)
            if (arr[i] < arr[i - 1])
            {
                swap(&arr[i], &arr[i - 1]);
                swapped = 1;
            }
    } while (swapped);
    toString(arr, n);
}

void countingSort(int arr[], int n)
{
    toString(arr, n);
    int output[10];

    // Find the largest element of the array
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    // The size of count must be at least (max+1) but
    // we cannot declare it as int count(max+1) in C as
    // it does not support dynamic memory allocation.
    // So, its size is provided statically.
    int count[10];

    // Initialize count array with all zeros.
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // Store the count of each element
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    toString(arr, n);
}

void cycleSort(int arr[], int n)
{
    toString(arr, n);
    for (int cycleStart = 0; cycleStart < n - 1; cycleStart++)
    {
        int item = arr[cycleStart];

        int pos = cycleStart;
        for (int i = cycleStart + 1; i < n; i++)
            if (arr[i] < item)
                pos++;

        if (pos == cycleStart)
            continue;

        while (item == arr[pos])
            pos++;

        int temp = arr[pos];
        arr[pos] = item;

        while (pos != cycleStart)
        {
            pos = cycleStart;
            for (int i = cycleStart + 1; i < n; i++)
                if (arr[i] < item)
                    pos++;

            while (item == arr[pos])
                pos++;

            temp = arr[pos];
            arr[pos] = item;
        }
    }
    toString(arr, n);
}

void beadSort(int *a, int len)
{
    //Only for + integers
    toString(a, len);
    int i, j, max, sum;
    unsigned char *beads;
    #define BEAD(i, j) beads[i * max + j]

    for (i = 1, max = a[0]; i < len; i++)
        if (a[i] > max)
            max = a[i];

    beads = calloc(1, max * len);

    /* mark the beads */
    for (i = 0; i < len; i++)
        for (j = 0; j < a[i]; j++)
            BEAD(i, j) = 1;

    for (j = 0; j < max; j++)
    {
        /* count how many beads are on each post */
        for (sum = i = 0; i < len; i++)
        {
            sum += BEAD(i, j);
            BEAD(i, j) = 0;
        }
        /* mark bottom sum beads */
        for (i = len - sum; i < len; i++)
            BEAD(i, j) = 1;
    }

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < max && BEAD(i, j); j++)
            ;
        a[i] = j;
    }
    free(beads);
    toString(a, len);
}

/*void sleepSort(int arr[], int n) {
    pthread_t threads[n];

    // Sleep function for each element
    for (int i = 0; i < n; i++)
        pthread_create(&threads[i], NULL, (void *(*)(void *))sleep, (void *)(intptr_t)arr[i]);

    // Wait for all threads to finish
    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);
}*/