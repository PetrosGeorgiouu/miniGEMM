#include "paralleladd.h"

#include <vector>
#include <algorithm>
#include <thread>
#include <cassert>
#include <iostream>

void add_rows_worker(const std::vector<std::vector<float>> &A,
                     std::vector<std::vector<float>> &B,
                     int start_row,
                     int end_row)
{
  for (int i = start_row; i < end_row; i++)
  {
    for (int j = 0; j < B[i].size(); j++)
    {
      B[i][j] += A[i][j];
    }
  }
}

void parallel_add_matrices(const std::vector<std::vector<float>> &A,
                           std::vector<std::vector<float>> &B, int p)
{
  int n = B.size();
  assert(p > 0);
  assert(n > 0);
  int num_threads = std::min(n, p);
  std::vector<std::thread> threads;
  threads.reserve(num_threads);

  int base_rows = n / num_threads;
  int extra = n % num_threads;

  int start = 0;
  for (int t = 0; t < num_threads; t++)
  {
    int rows = base_rows + (t < extra ? 1 : 0);
    int end = start + rows;
    threads.emplace_back(add_rows_worker, std::cref(A), std::ref(B), start, end);
    start = end;
  }

  for (auto &t : threads)
  {
    t.join();
  }
}