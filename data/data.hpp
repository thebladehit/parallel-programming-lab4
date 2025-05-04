// ПЗВКС
// Lab 4 (Програмування для комп’ютерних систем зі спільною пам’яттю)
// A = p*(sort(d*B + Z*MM) * (MX*MT) )+ (B*Z) * Z
// MM, B, MX - 1 thread
// p - 3 thread
// A, Z, MT, d - 4 thread
// Ярмолка Богдан Ігорович
// ІМ-22
// 03.05.2025

namespace data {
  constexpr int N = 4;
  constexpr int P = 4;
  constexpr int H = N / P;

  // Variables
  inline int p, d;

  // Vectors
  inline int A[N], B[N], Z[N];

  // Matrixes
  inline int MM[N][N], MX[N][N], MT[N][N];

  void printVector(int V[N]);

  void fillVectorByNums(int V[N], int num);
  void fillMatrixByNums(int M[N][N], int num);

  void calculate_dBZMM(int resV[N], int d, int start, int end);
  void multiplyVectorOnMatrix(int V[N], int M[N][N], int resV[N], int start, int end);
  void multiplyVectorOnScalar(int V[N], int num, int resV[N], int start, int end);
  void multiplyMatrices(int firstM[N][N], int secondM[N][N], int resM[N][N], int start, int end);
  void sumVectors(int firstV[N], int secondV[N], int resV[N], int start, int end);
  void calculateA(int p, int dBZMM[N], int a, int start, int end);

  void sort(int V[], int left, int right);
  void merge(int V[], int left, int mid, int right);

  int calculateElemMultiplyVectorOnMatrix(int idx, int V[N], int M[N][N]);
  int multiplyVectorOnVector(int firstV[N], int secondV[N], int start, int end);
}