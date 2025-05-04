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
#include "data/data.hpp"
#include <omp.h>
#include <chrono>

int main() {
  // execution time 
  auto start = std::chrono::high_resolution_clock::now();

  // intermediate variables
  int dBZMM[data::N];
  int a = 0;

  std::cout << "Main thread started" << std::endl;

  // input data from 3 threads
  #pragma omp parallel num_threads(3)
  {
    #pragma omp sections 
    {
      #pragma omp section 
      {
        data::fillMatrixByNums(data::MM, 1);
        data::fillMatrixByNums(data::MX, 1);
        data::fillVectorByNums(data::B, 1);
      }
      #pragma omp section 
      {
        data::p = 1;
      }
      #pragma omp section 
      {
        data::fillVectorByNums(data::Z, 1);
        data::fillMatrixByNums(data::MT, 1);
        data::d = 1;
      }
    }
  }

  // calculations
  #pragma omp parallel num_threads(data::P) shared(dBZMM)
  {
    int t_id = omp_get_thread_num();
    int start = t_id * data::H;
    int end = start + data::H;
    int d, p;

    // log about starting
    #pragma omp critical
    {
      std::cout << "Thread" << t_id + 1 << " started" << std::endl;
    }

    #pragma omp critical(CS1)
    {
      d = data::d;
    }

    // sort(d*B + Z*MM)
    data::calculate_dBZMM(dBZMM, d, start, end);
    data::sort(dBZMM, start, end - 1);

    #pragma omp barrier
    if (t_id == 0 || t_id == 2) {
      data::sort(dBZMM, start, end + data::H - 1);
    }

    #pragma omp barrier
    if (t_id == 0) {
      data::sort(dBZMM, start, data::N - 1);
    }

    #pragma omp barrier

    // (B * Z)
    int ai = 0;
    ai = data::multiplyVectorOnVector(data::B, data::Z, start, end);

    #pragma omp critical(CS2)
    {
      a += ai;
    }

    #pragma omp barrier

    // copy p
    #pragma omp critical(CS3)
    {
      p = data::p;
    }

    // copy a (B * Z)
    #pragma omp critical(CS4)
    {
      ai = a;
    }

    // p * dBZMM * (MX*MT) + a * Z
    data::calculateA(p, dBZMM, ai, start, end);

    
    // wait for calculation
    #pragma omp barrier

    if (t_id == 3) {
      #pragma omp critical
      {
        data::printVector(data::A);
      }
    }

    #pragma omp critical
    {
      std::cout << "Thread" << t_id + 1 << " finished" << std::endl;
    }
  }


  std::cout << "Main thread finished" << std::endl;

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  std::cout << "Execution time: " << duration.count() << " s\n";

  return 0;
}