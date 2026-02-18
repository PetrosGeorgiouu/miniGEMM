#include "bruteforce.h"
#include <iostream>

void bruteForceMatMult(const float *A, const float *B, float *C, int n,
                       int k, int m)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      for (int l = 0; l < k; l++)
      {
        C[i * m + j] += A[i * k + l] * B[l * m + j];
      }
    }
  }
}
