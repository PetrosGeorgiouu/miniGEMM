#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <cmath>
#include <algorithm>
#include "paralleladd.h"

std::vector<std::vector<float>> make_random_matrix(int rows, int cols)
{
  std::vector<std::vector<float>> M(rows, std::vector<float>(cols));

  std::mt19937 gen(42);
  std::uniform_real_distribution<float> dist(0.0f, 10.0f);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      M[i][j] = dist(gen);
    }
  }

  return M;
}

// Brute-force serial addition: B += A
void brute_force_add_matrices(const std::vector<std::vector<float>> &A,
                              std::vector<std::vector<float>> &B)
{
  for (int i = 0; i < (int)A.size(); i++)
  {
    for (int j = 0; j < (int)A[i].size(); j++)
    {
      B[i][j] += A[i][j];
    }
  }
}

bool matrices_equal(const std::vector<std::vector<float>> &A,
                    const std::vector<std::vector<float>> &B,
                    float eps = 1e-5f)
{
  if (A.size() != B.size())
    return false;

  for (int i = 0; i < (int)A.size(); i++)
  {
    if (A[i].size() != B[i].size())
      return false;

    for (int j = 0; j < (int)A[i].size(); j++)
    {
      if (std::fabs(A[i][j] - B[i][j]) > eps)
        return false;
    }
  }

  return true;
}

int main()
{
  // Try 4000x4000 first. Increase to 6000x6000 or 8000x8000 if your RAM can handle it.
  const int rows = 4000;
  const int cols = 4000;

  int p = std::thread::hardware_concurrency();
  if (p == 0)
  {
    p = 4;
  }

  std::cout << "Generating matrices of size " << rows << " x " << cols << "...\n";
  std::cout << "Using " << p << " threads.\n";

  const std::vector<std::vector<float>> A = make_random_matrix(rows, cols);
  std::vector<std::vector<float>> B_parallel = make_random_matrix(rows, cols);
  std::vector<std::vector<float>> B_serial = B_parallel;

  auto start_parallel = std::chrono::high_resolution_clock::now();
  parallel_add_matrices(A, B_parallel, p);
  auto end_parallel = std::chrono::high_resolution_clock::now();

  auto start_serial = std::chrono::high_resolution_clock::now();
  brute_force_add_matrices(A, B_serial);
  auto end_serial = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> parallel_time = end_parallel - start_parallel;
  std::chrono::duration<double> serial_time = end_serial - start_serial;

  std::cout << "\nParallel time: " << parallel_time.count() << " seconds\n";
  std::cout << "Serial time:   " << serial_time.count() << " seconds\n";

  if (parallel_time.count() > 0.0)
  {
    std::cout << "Speedup:       " << serial_time.count() / parallel_time.count() << "x\n";
  }

  if (matrices_equal(B_parallel, B_serial))
  {
    std::cout << "Check passed: results match.\n";
  }
  else
  {
    std::cout << "Check failed: results do not match.\n";
  }

  return 0;
}