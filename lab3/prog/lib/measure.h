#pragma once

#include "algorithms.h"
#include <ctime>

enum class Ordering
{
    Random = 0,
    Forward = 1,
    Backward = 2
};

void TimeMeasure(int start, int maxLen, int step, int iters, Ordering order = Ordering::Random);