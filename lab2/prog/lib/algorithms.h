#pragma once

#include <iostream>
#include <unordered_map>

#include "matrix.h"

namespace Multiply
{
    Matrix Common(const Matrix &m1, const Matrix &m2);
    Matrix Vinograd(const Matrix &m1, const Matrix &m2);
    Matrix VinogradOpt(const Matrix &m1, const Matrix &m2);
};