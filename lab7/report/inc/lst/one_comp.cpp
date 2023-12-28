 int Algs::bin_search_one_comp(const std::vector<int> &arr, int x)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low != high)
    {
        int mid = ceil(double(low + high) / 2.0);
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
        return low;
    }

    return -1;
}
