#include "matrix.h"

#include <iostream>
#include <iomanip>
#include <cstring>

int **Matrix::Allocate(int rows, int cols)
{
    int **mat = static_cast<int **>(malloc(rows * sizeof(int *)));

    if (mat)
    {
        for (int i = 0; i < rows; ++i)
        {
            int *ptr = static_cast<int *>(malloc(cols * sizeof(int)));
            if (ptr)
            {
                mat[i] = ptr;
            }
            else
            {
                Free(mat, rows);
            }
        }
    }
    return mat;
}

int **Matrix::Allocate(int rows, int cols, int value)
{
    int **mat = static_cast<int **>(malloc(rows * sizeof(int *)));

    if (mat)
    {
        for (int i = 0; i < rows; ++i)
        {
            int *ptr = static_cast<int *>(malloc(cols * sizeof(int)));
            if (ptr)
            {
                mat[i] = ptr;
                for (int j = 0; j < cols; ++j)
                    mat[i][j] = value;
            }
            else
            {
                Matrix::Free(mat, rows);
            }
        }
    }
    return mat;
}

void Matrix::Free(int **mat, int rows)
{
    if (mat)
    {
        for (auto i = 0; i < rows; ++i)
        {
            std::free(mat[i]);
        }
        std::free(mat);
    }
}

void Matrix::Print(int **mat, const std::wstring &word1, const std::wstring &word2)
{
    int len1 = word1.length();
    int len2 = word2.length();

    for (int i = 0; i <= len2 + 1; ++i)
    {
        std::wcout << std::setw(8) << L"";

        for (int j = 0; j <= len1 + 1; ++j)
        {
            if (i > 1 && j == 0)
                std::wcout << word2[i - 2];
            else if (i == 0 && j > 1)
                std::wcout << word1[j - 2];
            else if (i > 0 && j > 0)
                std::wcout << mat[i - 1][j - 1];
            else
                std::wcout << " ";

            std::wcout << " ";
        }
        std::wcout << L"\n";
    }
}
