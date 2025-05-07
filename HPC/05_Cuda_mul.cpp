#include <iostream>

#define N 10

// Function for matrix multiplication
void matrixMul(int a[N][N], int b[N][N], int c[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;  // Initialize the result matrix element to 0
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];  // Perform multiplication and accumulate the result
            }
        }
    }
}

int main() {
    int a[N][N], b[N][N], c[N][N];

    // Fill the matrices 'a' and 'b'
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = i + j;  // Example values for matrix 'a'
            b[i][j] = i - j;  // Example values for matrix 'b'
        }
    }

    // Perform matrix multiplication
    matrixMul(a, b, c);

    // Display the result
    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix B:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << b[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix C (Result of A x B):" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
//g++ -o 05_cuda_mul 05_cuda_mul.cpp
//./05_cuda_mul