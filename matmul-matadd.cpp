#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Constants
#define VECTOR_SIZE 100000000
#define MATRIX_SIZE 1000

void vectorAddition() {
    vector<float> A(VECTOR_SIZE), B(VECTOR_SIZE), C(VECTOR_SIZE);

    // Initialize vectors in parallel
    #pragma omp parallel for
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        A[i] = i * 1.0f;
        B[i] = i * 2.0f;
    }

    // Add vectors in parallel
    #pragma omp parallel for
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        C[i] = A[i] + B[i];
    }

    // Display first 10 results
    cout << "First 10 elements of vector addition result:\n";
    for (int i = 0; i < 10; ++i) {
        cout << "C[" << i << "] = " << C[i] << endl;
    }
}

void matrixMultiplication() {
    vector<vector<float>> A(MATRIX_SIZE, vector<float>(MATRIX_SIZE));
    vector<vector<float>> B(MATRIX_SIZE, vector<float>(MATRIX_SIZE));
    vector<vector<float>> C(MATRIX_SIZE, vector<float>(MATRIX_SIZE, 0.0f));

    // Initialize matrices
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < MATRIX_SIZE; ++i)
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }

    // Matrix multiplication
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < MATRIX_SIZE; ++i)
        for (int j = 0; j < MATRIX_SIZE; ++j)
            for (int k = 0; k < MATRIX_SIZE; ++k)
                C[i][j] += A[i][k] * B[k][j];

    // Print a small part of the result
    cout << "Top-left 5x5 of matrix multiplication result:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            cout << C[i][j] << " ";
        cout << endl;
    }
}

int main() {
    int choice;
    cout << "Choose an operation:\n";
    cout << "1. Vector Addition (size: " << VECTOR_SIZE << ")\n";
    cout << "2. Matrix Multiplication (" << MATRIX_SIZE << "x" << MATRIX_SIZE << ")\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        vectorAddition();
    } else if (choice == 2) {
        matrixMultiplication();
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
