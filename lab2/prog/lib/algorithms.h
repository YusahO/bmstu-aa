#pragma once

#include <iostream>
#include <unordered_map>

#include "matrix.h"

namespace Multiply
{
    Matrix Common(const Matrix &m1, const Matrix &m2);
    Matrix Winograd(const Matrix &m1, const Matrix &m2);
    Matrix WinogradOpt(const Matrix &m1, const Matrix &m2);
};
