

#include <iostream>
#include <vector>
#include <omp.h>

#define N 100000000  
using namespace std;

int main() {
    vector<float> A(N), B(N), C(N);

    
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        A[i] = i * 1.0f;
        B[i] = i * 2.0f;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        C[i] = A[i] + B[i];
    }

    
    for (int i = 0; i < 10; ++i) {
        cout << "C[" << i << "] = " << C[i] << endl;
    }

    return 0;
}

