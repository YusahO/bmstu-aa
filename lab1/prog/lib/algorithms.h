#pragma once

#include <iostream>

#include "matrix.h"

constexpr size_t DP_MatrixSize = 1000;

using NonRecursiveFunc = int(*)(const std::wstring &, const std::wstring &, bool);
using RecursiveFunc = int(*)(const std::wstring &, const std::wstring &, int, int);
using RecursiveCacheFunc = int(*)(const std::wstring &, const std::wstring &, int, int, int **);

int LevNonRec(const std::wstring &word1, const std::wstring &word2, bool verbose = false);
int DamLevNonRec(const std::wstring& word1, const std::wstring& word2, bool verbose = false);
int DamLevRec(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2);
int DamLevRecCache(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2, int **dp);