#include "bruteforce.h"

void bruteforceGEMM(const float *A, const float *B, float *C, float alpha, float beta,
                    int n, int k, int m)
{
  float AB[n][m];

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      for (int l = 0; l < k; l++)
      {
        AB[i][j] += A[i * k + l] * B[l * m + j];
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      AB[i][j] *= alpha;
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      C[i * m + j] *= beta;
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      C[i * m + j] += AB[i][j];
    }
  }
}
