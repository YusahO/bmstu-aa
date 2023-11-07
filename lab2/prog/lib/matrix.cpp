#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

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

void Matrix::FillRandom(int maxVal)
{
    for (size_t i = 0; i < m_Matrix.size(); ++i)
        for (size_t j = 0; j < m_Matrix[0].size(); ++j)
            m_Matrix[i][j] = std::rand() % maxVal;
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
        std::cout << "[ ";
        for (auto v : row)
            os << std::right << std::setw(7) << v;
        os << " ]" << std::endl;
    }
    return os;
}
