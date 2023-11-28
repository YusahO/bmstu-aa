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
    void PancakeSort(std::vector<int> &arr)
    {
        const int length = arr.size();
        if (length < 2)
            return;

        for (int i = length; i > 1; --i)
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
    }

    void GnomeSort(std::vector<int> &arr)
    {
        int i = 1;
        const int length = (int)arr.size();
        while (i < length)
        {
            if (i > 0 && arr[i - 1] > arr[i])
            {
                int swap = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = swap;
                --i;
            }
            else
            {
                ++i;
            }
        }
    }

    void QuickSort(std::vector<int> &arr, int start, int end)
    {
        if (start < 0 || end < 0 || start >= end)
            return;

        int pivot = arr[start];
        int l = start - 1, r = end + 1;
        
        while (true)
        {
            do
            {
                ++l;
            } while (arr[l] < pivot);
            do
            {
                --r;
            } while (arr[r] > pivot);

            if (l >= r)
                break;

            int swap = arr[l];
            arr[l] = arr[r];
            arr[r] = swap;
        }

        QuickSort(arr, start, r);
        QuickSort(arr, r + 1, end);
    }
}