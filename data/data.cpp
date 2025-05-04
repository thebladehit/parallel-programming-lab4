// ПЗВКС
// Lab 4 (Програмування для комп’ютерних систем зі спільною пам’яттю)
// A = p*(sort(d*B + Z*MM) * (MX*MT) )+ (B*Z) * Z
// MM, B, MX - 1 thread
// p - 3 thread
// A, Z, MT, d - 4 thread
// Ярмолка Богдан Ігорович
// ІМ-22
// 03.05.2025

#include <iostream>
#include "data.hpp"
#include <omp.h>

namespace data {
  void printVector(int V[N]) {
    for (int i = 0; i < N; i++) {
      std::cout << V[i] << " ";
    }
    std::cout << std::endl;
  }

  void fillVectorByNums(int V[N], int num) {
    for (int i = 0; i < N; i++) {
      V[i] = num;      ;
    }
  }

  void fillMatrixByNums(int M[N][N], int num) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        M[i][j] = num;
      }
    }
  }

  void calculate_dBZMM(int resV[N], int d, int start, int end) {
    for (int i = start; i < end; i++) {
      resV[i] = d * B[i] + calculateElemMultiplyVectorOnMatrix(i, Z, MM);
    }
  }

  void multiplyVectorOnMatrix(int V[N], int M[N][N], int resV[N], int start, int end) {
    // #pragma omp for // add for more paralelism
    for (int i = start; i < end; i++) {
      resV[i] = 0;
      for (int j = 0; j < N; j++) {
        resV[i] += V[j] * M[j][i];
      }
    }
  }

  void multiplyVectorOnScalar(int V[N], int num, int resV[N], int start, int end) {
  // #pragma omp for // add for more paralelism
    for (int i = start; i < end; i++) {
      resV[i] = V[i] * num;
    }
  }

  void multiplyMatrices(int firstM[N][N], int secondM[N][N], int resM[N][N], int start, int end) {
    // #pragma omp for // add for more paralelism
    for (int i = 0; i < N; i++) {
      for (int j = start; j < end; j++) {
        resM[i][j] = 0;
        for (int k = 0; k < N; k++) {
          resM[i][j] += firstM[i][k] * secondM[k][j];
        }
      }
    }
  }

  void sumVectors(int firstV[N], int secondV[N], int resV[N], int start, int end) {
    // #pragma omp for // add for more paralelism
    for (int i = start; i < end; i++) {
      resV[i] = firstV[i] + secondV[i];
    }
  }

  void calculateA(int p, int dBZMM[N], int a, int start, int end) {
    int MXMT[N][N];
    int dBZMMMXMT[N];
    int pdBZMMMXMT[N];
    int aZ[N];

    multiplyMatrices(MX, MT, MXMT, start, end);
    multiplyVectorOnMatrix(dBZMM, MXMT, dBZMMMXMT, start, end);
    multiplyVectorOnScalar(dBZMMMXMT, p, pdBZMMMXMT, start, end);
    multiplyVectorOnScalar(Z, a, aZ, start, end);
    sumVectors(pdBZMMMXMT, aZ, A, start, end);
  }

  void sort(int V[], int left, int right) {
    if (left < right) {
      int mid = left + (right - left) / 2;

      sort(V, left, mid);
      sort(V, mid + 1, right);

      merge(V, left, mid, right);
    }
  }

  void merge(int V[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
      L[i] = V[left + i];
    for (int i = 0; i < n2; i++)
      R[i] = V[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        V[k] = L[i];
        i++;
      } else {
        V[k] = R[j];
        j++;
      }
      k++;
    }

    while (i < n1) {
      V[k] = L[i];
      i++;
      k++;
    }

    while (j < n2) {
      V[k] = R[j];
      j++;
      k++;
    }
  }

  int calculateElemMultiplyVectorOnMatrix(int idx, int V[N], int M[N][N]) {
    int res = 0;
    for (int i = 0; i < N; i++) {
      res += V[i] * M[i][idx];
    }
    return res;
  }

  int multiplyVectorOnVector(int firstV[N], int secondV[N], int start, int end) {
    int res = 0;

    for (int i = start; i < end; i++) {
      res += firstV[i] * secondV[i];
    }

    return res;
  }
}