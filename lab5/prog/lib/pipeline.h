#pragma once

#include "ts_queue.h"
#include "pipe_request.h"
#include "algorithms.h"
#include "utils.h"

#include <thread>

namespace std
{
    template <typename T>
    ostream &operator<<(ostream &os, const vector<T> &arr)
    {
        os << "[ ";
        for (const T &v : arr)
            cout << v << " ";
        os << "]";
        return os;
    }
}

using ProcFn = void (*)(int,
                        const std::vector<std::string> &,
                        std::tuple<int, double, double, int>,
                        bool);

struct stages_t
{
    parsed_dataset_request parsed;
    embedded_dataset_request embedded;
    clusterized_request clusterized;
};

void consequent(int req_cnt,
                const std::vector<std::string> &datasets,
                std::tuple<int, double, double, int> cls_params,
                bool verbose = true);

void concurrent(int req_cnt,
                const std::vector<std::string> &datasets,
                std::tuple<int, double, double, int> cls_params,
                bool verbose = true);