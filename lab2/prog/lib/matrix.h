#pragma once

#include <cstddef>
#include <vector>
#include <string>

class Matrix
{
public:
    Matrix() = default;
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int val);

    size_t rows() const { return m_Matrix.size(); }
    size_t columns() const { return m_Matrix[0].size(); }
    size_t size() const { return m_Matrix.size(); }

    Matrix slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) const;
    static Matrix combine(const Matrix &a11, const Matrix &a12, const Matrix &a21, const Matrix &a22);

    void fillRandom(int maxVal = 1000);

    static Matrix fromFile(const std::string &filename);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
    std::vector<int> &operator[](int i) { return m_Matrix[i]; }
    const std::vector<int> &operator[](int i) const { return m_Matrix[i]; }

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;

private:
    std::vector<std::vector<int>> m_Matrix;
};
