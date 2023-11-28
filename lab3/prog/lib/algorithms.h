#pragma once

#include <vector>

#include <tuple>

using SortFn = void (*)(std::vector<int> &);
using QSortFn = void (*)(std::vector<int> &, int, int);

namespace Sort
{
    void PancakeSort(std::vector<int> &arr);
    void GnomeSort(std::vector<int> &arr);
    void QuickSort(std::vector<int> &arr, int start, int end);
}
