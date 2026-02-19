#include "bruteforce.h"
#include <iostream>

int main()
{
  float A[4][5] = {{1, 2, 3, 4, 5},
                   {6, 2, 3, 5, 5},
                   {8, 4, 0, -1, -5},
                   {103, 242, -34, 423, 245}};
  float B[5][3] = {{6, 1, 5},
                   {3, 4, 5},
                   {10, 8, 4},
                   {6, 4, 3},
                   {8, 9, 0}};
  float C[4][3] = {};
  bruteForceMatMult(*A, *B, *C, 4, 5, 3);

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      std::cout << C[i][j] << " ";
    }
    std::cout << "\n";
  }
}