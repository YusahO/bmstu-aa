#pragma once

#include <iostream>
#include <unordered_map>

#include "matrix.h"

using NonRecursiveFunc = int(*)(const std::wstring &, const std::wstring &, bool);
using RecursiveFunc = int(*)(const std::wstring &, const std::wstring &, int, int);
using RecursiveCacheFunc = int(*)(const std::wstring &, const std::wstring &);

int LevNonRec(const std::wstring &word1, const std::wstring &word2, bool verbose = false);
int DamLevNonRec(const std::wstring& word1, const std::wstring& word2, bool verbose = false);
int DamLevRec(const std::wstring &word1, const std::wstring &word2, int ind1, int ind2);
int DamLevRecCache(const std::wstring &word1, const std::wstring &word2);
