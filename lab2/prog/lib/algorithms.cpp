#include "algorithms.h"

namespace Multiply
{
    Matrix Common(const Matrix &m1, const Matrix &m2)
    {
        Matrix res(m1.rows(), m2.columns(), 0);
        for (int i = 0; i < m1.rows(); ++i)
        {
            for (int j = 0; i < m2.columns(); ++j)
            {
                for (int k = 0; k < m1.columns(); ++k)
                {
                    res[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
        return res;
    }

    Matrix Vinograd(const Matrix &m1, const Matrix &m2)
    {
        
    }
}