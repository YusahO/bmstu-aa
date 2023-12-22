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

struct stages_t
{
    parsed_dataset_request parsed;
    embedded_dataset_request embedded;
    clusterized_request clusterized;
};

void consequent();
void concurrent();