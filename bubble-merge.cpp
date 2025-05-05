#include <iostream>
#include <omp.h>
#include <algorithm>

using namespace std;

// ---------- Merge Sort Functions ----------

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] < right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
}

void mergeSortSequential(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortParallel(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);
            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

// ---------- Bubble Sort Functions ----------

void bubbleSortSequential(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void bubbleSortParallel(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// ---------- Utility ----------

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// ---------- Main ----------

int main() {
    int choice;
    cout << "Choose Sorting Algorithm:\n";
    cout << "1. Merge Sort (Sequential vs Parallel)\n";
    cout << "2. Bubble Sort (Sequential vs Parallel)\n";
    cout << "Enter choice: ";
    cin >> choice;

    int arr1[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arr2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int N = sizeof(arr1) / sizeof(arr1[0]);

    if (choice == 1) {
        double start = omp_get_wtime();
        mergeSortSequential(arr1, 0, N - 1);
        double end = omp_get_wtime();
        cout << "Merge Sort Sequential Time: " << end - start << " sec\n";

        start = omp_get_wtime();
        mergeSortParallel(arr2, 0, N - 1);
        end = omp_get_wtime();
        cout << "Merge Sort Parallel Time: " << end - start << " sec\n";

        cout << "Sorted Array (Parallel): ";
        printArray(arr2, N);
    }
    else if (choice == 2) {
        double start = omp_get_wtime();
        bubbleSortSequential(arr1, N);
        double end = omp_get_wtime();
        cout << "Bubble Sort Sequential Time: " << end - start << " sec\n";

        start = omp_get_wtime();
        bubbleSortParallel(arr2, N);
        end = omp_get_wtime();
        cout << "Bubble Sort Parallel Time: " << end - start << " sec\n";

        cout << "Sorted Array (Parallel): ";
        printArray(arr2, N);
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
