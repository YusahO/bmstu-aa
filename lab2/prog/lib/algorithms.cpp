#include "algorithms.h"

namespace Multiply
{
    Matrix Common(const Matrix &m1, const Matrix &m2)
    {
        size_t rows1 = m1.rows();
        size_t cols1 = m1.columns();
        size_t cols2 = m2.columns();

        Matrix res(rows1, cols2, 0);

        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < cols2; ++j)
                for (size_t k = 0; k < cols1; ++k)
                    res[i][j] = res[i][j] + m1[i][k] * m2[k][j];

        return res;
    }

    Matrix Winograd(const Matrix &m1, const Matrix &m2)
    {
        size_t rows1 = m1.rows(); // a
        size_t cols1 = m1.columns(); // b
        size_t cols2 = m2.columns(); // c

        Matrix res(rows1, rows1);

        std::vector<int> row_factors(rows1, 0);
        std::vector<int> col_factors(cols2, 0);

        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < cols1 / 2; ++j)
                row_factors[i] = row_factors[i] + m1[i][2 * j] * m1[i][2 * j + 1];

        for (size_t i = 0; i < cols2; ++i)
            for (size_t j = 0; j < cols1 / 2; ++j)
                col_factors[i] = col_factors[i] + m2[2 * j][i] * m2[2 * j + 1][i];

        for (size_t i = 0; i < rows1; ++i)
        {
            for (size_t j = 0; j < cols2; ++j)
            {
                res[i][j] = -row_factors[i] - col_factors[j];
                for (size_t k = 0; k < cols1 / 2; ++k)
                {
                    res[i][j] = res[i][j] + (m1[i][2 * k] + m2[2 * k + 1][j]) *
                                (m1[i][2 * k + 1] + m2[2 * k][j]);
                }
            }
        }

        if (cols1 % 2)
        {
            for (size_t i = 0; i < rows1; ++i)
                for (size_t j = 0; j < cols2; ++j)
                    res[i][j] = res[i][j] + m1[i][cols1 - 1] *
                                m2[cols1 - 1][j];
        }

        return res;
    }

    Matrix WinogradOpt(const Matrix &m1, const Matrix &m2)
    {
        size_t rows1 = m1.rows(); // a
        size_t cols1 = m1.columns(); // b
        size_t cols2 = m2.columns(); // c

        Matrix res(rows1, rows1);

        std::vector<int> row_factors(rows1, 0);
        std::vector<int> col_factors(cols2, 0);

        size_t half_cols1 = cols1 / 2;

        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < half_cols1; ++j)
                row_factors[i] += m1[i][j << 1] * m1[i][(j << 1) + 1];

        for (size_t i = 0; i < cols2; ++i)
            for (size_t j = 0; j < half_cols1; ++j)
                col_factors[i] += m2[j << 1][i] * m2[(j << 1) + 1][i];

        for (size_t i = 0; i < rows1; ++i)
        {
            for (size_t j = 0; j < cols2; ++j)
            {
                res[i][j] = -row_factors[i] - col_factors[j];
                for (size_t k = 0; k < half_cols1; ++k)
                {
                    size_t k_shifted = k << 1;
                    res[i][j] += (m1[i][k_shifted] + m2[k_shifted + 1][j]) *
                        (m1[i][k_shifted + 1] + m2[k_shifted][j]);
                }
            }
        }

        if (cols1 % 2)
        {
            for (size_t i = 0; i < rows1; ++i)
                for (size_t j = 0; j < cols2; ++j)
                    res[i][j] += m1[i][cols1 - 1] *
                    m2[cols1 - 1][j];
        }

        return res;
    }

    Matrix Strassen(const Matrix &m1, const Matrix &m2)
    {
        size_t n = m1.rows() / 2;
        size_t rows = m1.rows();

        if (rows <= 2)
        {
            return Common(m1, m2);
        }

        auto a11 = m1.slice(0, n, 0, n);
        auto a12 = m1.slice(0, n, n, rows);
        auto a21 = m1.slice(n, rows, 0, n);
        auto a22 = m1.slice(n, rows, n, rows);

        auto b11 = m2.slice(0, n, 0, n);
        auto b12 = m2.slice(0, n, n, rows);
        auto b21 = m2.slice(n, rows, 0, n);
        auto b22 = m2.slice(n, rows, n, rows);

        auto p1 = Strassen(a11 + a22, b11 + b22);
        auto p2 = Strassen(a22, b21 - b11);
        auto p3 = Strassen(a11 + a12, b22);
        auto p4 = Strassen(a12 - a22, b21 + b22);
        auto p5 = Strassen(a11, b12 - b22);
        auto p6 = Strassen(a21 + a22, b11);
        auto p7 = Strassen(a11 - a21, b11 + b12);

        auto c11 = p1 + p2 - p3 + p4;
        auto c12 = p5 + p3;
        auto c21 = p6 + p2;
        auto c22 = p5 + p1 - p6 - p7;

        return Matrix::combine(c11, c12, c21, c22);
    }
}
