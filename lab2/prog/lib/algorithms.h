#pragma once

#include <iostream>
#include <unordered_map>

#include "matrix.h"

using MatMulFunc = Matrix(*) (const Matrix &, const Matrix &);

namespace Multiply
{
    Matrix Common(const Matrix &m1, const Matrix &m2);
    Matrix Winograd(const Matrix &m1, const Matrix &m2);
    Matrix WinogradOpt(const Matrix &m1, const Matrix &m2);
    Matrix Strassen(const Matrix &m1, const Matrix &m2);
};
