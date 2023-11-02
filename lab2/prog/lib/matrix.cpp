#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>

Matrix::Matrix(int rows, int cols)
    : m_Matrix(rows, std::vector<int>(cols))
{
    std::srand(std::time(nullptr));
}

Matrix::Matrix(int rows, int cols, int val)
    : Matrix(rows, cols)
{
    for (auto &row : m_Matrix)
        std::fill(row.begin(), row.end(), val);
}

void Matrix::FillRandom()
{
    for (auto &row : m_Matrix)
        for (auto v : row)
            v = std::rand() % 1000;
}

Matrix Matrix::FromFile(const std::string &filename)
{
    std::ifstream f{ filename };
    if (!f.is_open())
    {
        std::cerr << "Error opening file \"" << filename << "\"";
        return Matrix();
    }

    Matrix mat;
    std::string line;
    while (getline(f, line))
    {
        int v;
        std::vector<int> row;
        std::stringstream curRow(line);
        while (curRow)
        {
            curRow >> v;
            row.emplace_back(v);
        }
        mat.m_Matrix.emplace_back(std::move(row));
    }
    return mat;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (auto &row : mat.m_Matrix)
    {
        os << '\t';
        for (auto v : row)
            os << v << " ";
        os << std::endl;
    }
    return os;
}
