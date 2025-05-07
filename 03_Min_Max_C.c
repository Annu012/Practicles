// run using this command 
// g++ -fopenmp -o 03_Min_Max_C 03_Min_Max_C.c

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define N 1000000  // Size of the data
#define NUM_THREADS 8  // Number of threads to use in parallel

// Function to compute sum using parallel reduction
double parallelSum(int *data) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum) num_threads(NUM_THREADS)
    for (int i = 0; i < N; i++) {
        sum += data[i];
    }
    return sum;
}

// Function to compute max using parallel reduction
int parallelMax(int *data) {
    int max_val = INT_MIN;
    #pragma omp parallel for reduction(max:max_val) num_threads(NUM_THREADS)
    for (int i = 0; i < N; i++) {
        max_val = (data[i] > max_val) ? data[i] : max_val;
    }
    return max_val;
}

// Function to compute min using parallel reduction
int parallelMin(int *data) {
    int min_val = INT_MAX;
    #pragma omp parallel for reduction(min:min_val) num_threads(NUM_THREADS)
    for (int i = 0; i < N; i++) {
        min_val = (data[i] < min_val) ? data[i] : min_val;
    }
    return min_val;
}

// Function to compute average using parallel reduction
double parallelAverage(int *data) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum) num_threads(NUM_THREADS)
    for (int i = 0; i < N; i++) {
        sum += data[i];
    }
    return sum / N;
}

int main() {
    // Create a large dataset with random values
    int *data = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        data[i] = rand() % 1000;  // Random number between 0 and 999
    }

    // Perform parallel operations
    double sum = parallelSum(data);
    int max_val = parallelMax(data);
    int min_val = parallelMin(data);
    double average = parallelAverage(data);

    // Display results
    printf("Sum: %.2f\n", sum);
    printf("Max: %d\n", max_val);
    printf("Min: %d\n", min_val);
    printf("Average: %.2f\n", average);

    // Free memory
    free(data);

    return 0;
}
