// run using this command 
// g++ -fopenmp -o 02_Bubble_Merger_sort 02_Bubble_Merger_sort.c


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10000

// Function to generate random array
void generateRandomArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 10000;
}

// Function to copy array
void copyArray(int* src, int* dest, int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}

// Sequential Bubble Sort
void sequentialBubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

// Parallel Bubble Sort (Odd-Even Transposition)
void parallelBubbleSort(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int phase = i % 2;
        #pragma omp parallel for
        for (int j = phase; j < size - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Merge function
void merge(int* arr, int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));

    while (i <= mid && j <= right)
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (int i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];

    free(temp);
}

// Sequential Merge Sort
void sequentialMergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int* arr, int left, int right, int depth) {
    if (left < right) {
        int mid = (left + right) / 2;
        if (depth < 4) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, depth + 1);
                #pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth + 1);
            }
        } else {
            sequentialMergeSort(arr, left, mid);
            sequentialMergeSort(arr, mid + 1, right);
        }
        merge(arr, left, mid, right);
    }
}

// Main function
int main() {
    int* original = (int*)malloc(SIZE * sizeof(int));
    int* arr1 = (int*)malloc(SIZE * sizeof(int));
    int* arr2 = (int*)malloc(SIZE * sizeof(int));
    double start, end;

    srand(time(0));
    generateRandomArray(original, SIZE);

    // Sequential Bubble Sort
    copyArray(original, arr1, SIZE);
    start = omp_get_wtime();
    sequentialBubbleSort(arr1, SIZE);
    end = omp_get_wtime();
    printf("Sequential Bubble Sort Time: %.4f sec\n", end - start);

    // Parallel Bubble Sort
    copyArray(original, arr2, SIZE);
    start = omp_get_wtime();
    parallelBubbleSort(arr2, SIZE);
    end = omp_get_wtime();
    printf("Parallel Bubble Sort Time: %.4f sec\n", end - start);

    // Sequential Merge Sort
    copyArray(original, arr1, SIZE);
    start = omp_get_wtime();
    sequentialMergeSort(arr1, 0, SIZE - 1);
    end = omp_get_wtime();
    printf("Sequential Merge Sort Time: %.4f sec\n", end - start);

    // Parallel Merge Sort
    copyArray(original, arr2, SIZE);
    start = omp_get_wtime();
    parallelMergeSort(arr2, 0, SIZE - 1, 0);
    end = omp_get_wtime();
    printf("Parallel Merge Sort Time: %.4f sec\n", end - start);

    free(original);
    free(arr1);
    free(arr2);
    return 0;
}
