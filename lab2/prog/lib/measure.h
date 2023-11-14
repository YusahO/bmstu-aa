#pragma once

#include "algorithms.h"
#include <ctime>

double MeasureCPUTime(const Matrix &m1, const Matrix &m2, MatMulFunc fn);

void TimeMeasure(int start, int maxLen, int iters);
