#ifndef PARALLELADD_H
#define PARALLELADD_H

#include <vector>

void add_rows_worker(const std::vector<std::vector<float>> &A,
                     std::vector<std::vector<float>> &B,
                     int start_row,
                     int end_row);

void parallel_add_matrices(const std::vector<std::vector<float>> &A,
                           std::vector<std::vector<float>> &B, int p);

#endif