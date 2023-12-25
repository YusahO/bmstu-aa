#pragma once

#include <vector>

namespace Algs
{
    int bin_search_one_comp(const std::vector<int> &arr, int x);
    int bin_search_two_comp(const std::vector<int> &arr, int x);

    void reset_cntr();
    std::pair<int, int> get_comp_amt();
}