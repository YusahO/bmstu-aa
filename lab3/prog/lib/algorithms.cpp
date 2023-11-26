#include "algorithms.h"

static void flip(std::vector<int> &arr, int m, int n)
{
    int swap, i;

    for (i = m; i < --n; i++)
    {
        swap = arr[i];
        arr[i] = arr[n];
        arr[n] = swap;
    }
}

namespace Sort
{
    int PancakeSort(std::vector<int> &arr)
    {
        if (arr.size() < 2)
            return 0;

        for (int i = arr.size(); i > 1; --i)
        {
            int maxNumPos = 0;
            for (int a = 0; a < i; ++a)
            {
                if (arr[a] > arr[maxNumPos])
                    maxNumPos = a;
            }

            if (maxNumPos == (i - 1))
                continue;

            if (maxNumPos >= 0)
            {
                flip(arr, maxNumPos, i);
            }
        }
        return 0;
    }

    void GnomeSort(std::vector<int> &arr)
    {
        int i = 1, j = 2;
        while (i < (int)arr.size())
        {
            if (arr[i - 1] < arr[i])
            {
                i = j++;
            }
            else
            {
                std::swap(arr[i - 1], arr[i]);
                --i;
                if (i == 0)
                    i = j++;
            }
        }
    }

    void QuickSort(std::vector<int> &arr, int start, int end)
    {
        int l = start, r = end;
        int piv = arr[(l + r) / 2];
        while (l <= r)
        {
            while (arr[l] < piv)
                l++;
            while (arr[r] > piv)
                r--;
            
            if (l <= r)
                std::swap(arr[l++], arr[r--]);
        }

        if (start < r)
            QuickSort(arr, start, r);
        if (end > l)
            QuickSort(arr, l, end);
    }

}