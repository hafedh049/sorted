#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define MIN_MERGE 32

// Function to perform Bubble Sort iteratively
void bubbleSort(int arr[], size_t n)
{
    toString(arr, n);
    int swapped;
    for (size_t i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (size_t j = 0; j < n - i - 1; j++)
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
void selectionSort(int arr[], size_t n)
{
    toString(arr, n);
    for (size_t i = 0; i < n - 1; i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; j++)
            if (arr[j] < arr[min_index])
                min_index = j;

        // Swap the found minimum element with the first element
        arr[min_index] = arr[min_index] + arr[i] - (arr[i] = arr[min_index]);

    }
    toString(arr, n);
}

void insertionSort(int arr[], size_t n)
{
    toString(arr, n);
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
    toString(arr, n);
}

void bucketSort(int arr[], size_t n)
{
    toString(arr, n);
    int max = arr[0];
    int min = arr[0];

    // Find the maximum and minimum values in the array
    for (size_t i = 1; i < n; i++)
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
    for (size_t i = 0; i < n; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    // Initialize each bucket
    for (size_t i = 0; i < n; i++)
        buckets[i][0] = 0; // Bucket size

    // Distribute elements into buckets
    for (size_t i = 0; i < n; i++)
    {
        size_t index = (arr[i] - min) / range;
        size_t size = ++buckets[index][0];
        buckets[index][size] = arr[i];
    }

    // Sort each bucket and update the original array
    size_t index = 0;
    for (size_t i = 0; i < n; i++)
    {
        size_t size = buckets[i][0];
        if (size > 0)
        {
            insertionSort(buckets[i] + 1, size);
            for (size_t j = 1; j <= size; j++)
                arr[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    free(buckets);
    toString(arr, n);
}

void shellSort(int arr[], size_t n)
{
    toString(arr, n);
    for (size_t gap = n / 2; gap > 0; gap /= 2)
        for (size_t i = gap; i < n; i++)
        {
            int temp = arr[i];
            size_t j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    toString(arr, n);
}

void merge(int arr[], size_t left_start, size_t mid, size_t right_end)
{
    toString(arr, right_end - left_start + 1);
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
    toString(arr, right_end - left_start + 1);
}

void insertionSorted(int arr[], size_t left, size_t right)
{
    for (size_t i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        size_t j = i - 1;
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void timSort(int arr[], size_t n)
{
    toString(arr, n);
    for (size_t i = 0; i < n; i += MIN_MERGE)
    {
        size_t left = i;
        size_t right = (i + MIN_MERGE - 1 < n - 1) ? (i + MIN_MERGE - 1) : (n - 1);
        insertionSorted(arr, left, right);
    }

    for (size_t size = MIN_MERGE; size < n; size = 2 * size)
    {
        for (size_t left = 0; left < n; left += 2 * size)
        {
            size_t mid = left + size - 1;
            size_t right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);
            merge(arr, left, mid, right);
        }
    }
    toString(arr, n);
}

void quickSort(int arr[], size_t n)
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
    *a = *a + *b - (*b = *a);
}

void countingSort(int arr[], size_t n)
{
    toString(arr, n);
    // Find the maximum element to determine the range
    int max = arr[0];
    for (size_t i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    // Create an array to store count of each element
    int *count = (int *)malloc((max + 1) * sizeof(int));

    // Initialize count array to 0
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // Store count of each element
    for (size_t i = 0; i < n; i++)
        count[arr[i]]++;

    // Modify count array to store actual position of elements
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Build the output array
    int *output = (int *)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back to the original array
    for (size_t i = 0; i < n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
    toString(arr, n);
}

size_t getNextGap(size_t gap)
{
    // Shrink gap by a factor of 1.3
    gap = (gap * 10) / 13;

    return (gap < 1) ? 1 : gap;
}

void combSort(int arr[], size_t n)
{
    toString(arr, n);
    size_t gap = n;

    bool swapped = true;

    while (gap != 1 || swapped)
    {
        gap = getNextGap(gap);

        swapped = false;

        for (size_t i = 0; i < n - gap; i++)
            if (arr[i] > arr[i + gap])
            {
                swap(&arr[i], &arr[i + gap]);
                swapped = true;
            }
    }
    toString(arr, n);
}

void pigeonholeSort(int arr[], size_t n)
{
    toString(arr, n);
    int min = arr[0];
    int max = arr[0];

    // Find the minimum and maximum values in the array
    for (size_t i = 1; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];

        if (arr[i] > max)
            max = arr[i];
    }

    size_t range = max - min + 1;
    int *pigeonholes = (int *)malloc(range * sizeof(int));

    // Initialize pigeonholes
    for (size_t i = 0; i < range; i++)
        pigeonholes[i] = 0;

    // Count occurrences of each element in the array
    for (size_t i = 0; i < n; i++)
        pigeonholes[arr[i] - min]++;

    // Fill the original array with sorted values
    size_t index = 0;
    for (size_t i = 0; i < range; i++)
        while (pigeonholes[i] > 0)
        {
            arr[index++] = i + min;
            pigeonholes[i]--;
        }

    free(pigeonholes);
    toString(arr, n);
}

void cycleSort(int arr[], size_t n)
{
    toString(arr, n);
    for (size_t cycleStart = 0; cycleStart < n - 1; cycleStart++)
    {
        int item = arr[cycleStart];

        size_t pos = cycleStart;
        for (size_t i = cycleStart + 1; i < n; i++)
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
            for (size_t i = cycleStart + 1; i < n; i++)
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

void cocktailShakerSort(int arr[], size_t n)
{
    toString(arr, n);
    int swapped;

    do
    {
        // Perform a forward pass
        swapped = 0;
        for (size_t i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }

        if (!swapped)
            break; // If no swapping occurred, the array is sorted

        // Perform a backward pass
        swapped = 0;
        for (size_t i = n - 1; i > 0; i--)
            if (arr[i] < arr[i - 1])
            {
                swap(&arr[i], &arr[i - 1]);
                swapped = 1;
            }
    } while (swapped);
    toString(arr, n);
}

void beadSort(int arr[], size_t n)
{
    toString(arr, n);
    int *beads = (int *)calloc(n, sizeof(int));

    // Store beads
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < arr[i]; j++)
            beads[i * n + j] = 1;

    // Count beads in each column
    for (size_t j = 0; j < n; j++)
    {
        size_t sum = 0;
        for (size_t i = 0; i < n; i++)
        {
            sum += beads[i * n + j];
            beads[i * n + j] = 0;
        }
        // Place beads in the array
        for (size_t i = n - sum; i < n; i++)
            beads[i * n + j] = 1;
    }

    // Retrieve sorted values
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n && beads[i * n + j]; j++)
            arr[i] = j + 1;

    free(beads);
    toString(arr, n);
}

/*void sleepSort(int arr[], size_t n) {
    pthread_t threads[n];

    // Sleep function for each element
    for (size_t i = 0; i < n; i++)
        pthread_create(&threads[i], NULL, (void *(*)(void *))sleep, (void *)(intptr_t)arr[i]);

    // Wait for all threads to finish
    for (size_t i = 0; i < n; i++)
        pthread_join(threads[i], NULL);
}*/