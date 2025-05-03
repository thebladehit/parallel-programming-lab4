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
  // constexpr int H = N / P; mb delete

  // Variables
  extern int p, d;

  // Vectors
  extern int A[N], B[N], Z[N];

  // Matrixes
  extern int MM[N][N], MX[N][N], MT[N][N];

  void hello(int i);
}