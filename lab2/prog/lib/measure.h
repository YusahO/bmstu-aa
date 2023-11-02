#pragma once

#include "algorithms.h"
#include <ctime>

std::wstring GenerateWord(unsigned long len);

double MeasureCPUTime(const std::wstring &word1, const std::wstring &word2, NonRecursiveFunc fn);
double MeasureCPUTime(const std::wstring &word1, const std::wstring &word2, RecursiveFunc fn);
double MeasureCPUTime(const std::wstring &word1, const std::wstring &word2, RecursiveCacheFunc fn);

void TimeMeasure(int maxLen, int iters);