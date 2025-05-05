

#include <iostream>
#include <vector>
#include <omp.h>

#define N 1000
using namespace std;

int main() {
    vector<vector<float>> A(N, vector<float>(N));
    vector<vector<float>> B(N, vector<float>(N));
    vector<vector<float>> C(N, vector<float>(N, 0.0f));

    // Initialize matrices
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }

    // Matrix multiplication using OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];

    // Print a small part of the result
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            cout << C[i][j] << " ";
        cout << endl;
    }

    return 0;
}

