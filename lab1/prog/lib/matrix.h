#pragma once

#include <cstddef>
#include <string>

namespace Matrix
{
    int **Allocate(int rows, int cols);
    int **Allocate(int rows, int cols, int value);
    void Free(int **mat, int rows);
    void Print(int **mat, const std::wstring &word1, const std::wstring &word2);
}