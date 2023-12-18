#pragma once

#include "algorithms.h"
#include <ctime>

// enum class Ordering
// {
//     Random = 0,
//     Forward = 1,
//     Backward = 2
// };

void TimeMeasureThreads(int start, int n_threads, int iters);
void TimeMeasureLength(int start, int max_len, int iters);