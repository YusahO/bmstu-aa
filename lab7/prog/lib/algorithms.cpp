#include "algorithms.h"

#include <cmath>

static std::pair<int, int> comps{};

int Algs::bin_search_two_comp(const std::vector<int> &arr, int x)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        ++comps.first;
        if (arr[mid] == x)
        {
            return mid;
        }
        else if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
        ++comps.first;
    }

    return -1;
}

int Algs::bin_search_one_comp(const std::vector<int> &arr, int x)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low != high)
    {
        int mid = ceil(double(low + high) / 2.0);
        ++comps.second;
        if (arr[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid;
        }
    }
    if (arr[low] == x)
    {
        ++comps.second;
        return low;
    }

    return -1;
}

void Algs::reset_cntr()
{
    comps = {0, 0};
}

std::pair<int, int> Algs::get_comp_amt()
{
    return comps;
}