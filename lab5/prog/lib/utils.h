#pragma once
#include <tuple>
#include <vector>
#include <string>

namespace utils
{
    int get_request_count();
    std::tuple<int, double, double, int> get_clust_params();
    std::vector<std::string> pick_datasets(int req_cnt);
}