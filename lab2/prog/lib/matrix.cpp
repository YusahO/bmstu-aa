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

Matrix Matrix::slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) const
{
    Matrix res(row_end - row_start, col_end - col_start);
    for (size_t i = row_start; i < row_end; ++i)
        for (size_t j = col_start; j < col_end; ++j)
            res[i - row_start][j - col_start] = m_Matrix[i][j];
    return res;
}

Matrix Matrix::combine(const Matrix &a11, const Matrix &a12, const Matrix &a21, const Matrix &a22)
{
    size_t n = a11.rows();
    size_t rows = n * 2;

    Matrix res(rows, rows);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            res.m_Matrix[i][j] = a11[i][j];
            res.m_Matrix[i][j + n] = a12[i][j];
            res.m_Matrix[i + n][j] = a21[i][j];
            res.m_Matrix[i + n][j + n] = a22[i][j];
        }
    }
    return res;
}

void Matrix::fillRandom(int maxVal)
{
    for (size_t i = 0; i < m_Matrix.size(); ++i)
        for (size_t j = 0; j < m_Matrix[0].size(); ++j)
            m_Matrix[i][j] = std::rand() % maxVal;
}

Matrix Matrix::fromFile(const std::string &filename)
{
    std::ifstream f{ filename };
    if (!f.is_open())
    {
        std::stringstream errStream;
        errStream << "Ошибка открытия файла \"" << filename << "\"\n";
        throw std::runtime_error(errStream.str());
    }

    Matrix mat;
    std::string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;
        int v;
        std::vector<int> row;
        std::stringstream curRow(line);
        while (curRow >> v)
        {
            row.emplace_back(v);
        }
        mat.m_Matrix.emplace_back(std::move(row));
    }
    return mat;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    size_t rows = m_Matrix.size();
    size_t cols = m_Matrix[0].size();
    Matrix res(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            res[i][j] = m_Matrix[i][j] + other.m_Matrix[i][j];
    return res;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    size_t rows = m_Matrix.size();
    size_t cols = m_Matrix[0].size();
    Matrix res(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            res[i][j] = m_Matrix[i][j] - other.m_Matrix[i][j];
    return res;
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
