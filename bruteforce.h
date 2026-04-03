#pragma once

void GEMM(const float *A, const float *B, float *C, float alpha, float beta,
          int n, int k, int m);