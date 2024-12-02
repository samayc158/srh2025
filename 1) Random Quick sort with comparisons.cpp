#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void display(int *A, int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int random_partition(int *A, int p, int r, int &comparisons) {
    int pivot = p + rand() % (r - p + 1);
    swap(A[pivot], A[r]);

    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        comparisons++; 
        if (A[j] < x) {
            i++;
            swap(A[i], A[j]);
        }
    }

    swap(A[i + 1], A[r]);
    return i + 1;
}

void quickSort(int *A, int p, int r, int &comparisons) {
    if (p < r) {
        int q = random_partition(A, p, r, comparisons);
        quickSort(A, p, q - 1, comparisons);
        quickSort(A, q + 1, r, comparisons);
    }
}

int main() {
    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    int *A = new int[n]; 
    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << "Original Array: ";
    display(A, n);

    int comparisons = 0; 
    quickSort(A, 0, n - 1, comparisons);

    cout << "Sorted Array: ";
    display(A, n);

    cout << "Number of comparisons: " << comparisons << endl;

    delete[] A;
    return 0;
}

