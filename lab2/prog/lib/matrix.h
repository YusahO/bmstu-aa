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

    int rows() const { return m_Matrix.size(); }
    int columns() const { return m_Matrix[0].size(); }

    void FillRandom();

    static Matrix FromFile(const std::string &filename);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
    std::vector<int> &operator[](int i) { return m_Matrix[i]; }
    const std::vector<int> &operator[](int i) const { return m_Matrix[i]; }

private:
    std::vector<std::vector<int>> m_Matrix;
};