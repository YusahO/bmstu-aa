#include "measure.h"

#include <vector>
#include <iostream>
#include <iomanip>

static long long GetThreadCpuTimeNs()
{
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t))
    {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

static std::vector<int> GetRandomArr(int n)
{
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i)
        vec[i] = rand() % 100;
    return vec;
}

static std::vector<int> GetForwardArr(int n)
{
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i)
        vec[i] = i;
    return vec;
}

static std::vector<int> GetBackwardArr(int n)
{
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i)
        vec[i] = n - i;
    return vec;
}

double MeasureCPUTime(std::vector<int> arr, SortFn fn)
{
    long long beg, end;

    beg = GetThreadCpuTimeNs();
    fn(arr);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

double MeasureCPUTime(std::vector<int> arr, QSortFn fn)
{
    long long beg, end;
    size_t n = arr.size() - 1;

    beg = GetThreadCpuTimeNs();
    fn(arr, 0, n);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

void PrintHeadTime()
{
    std::cout << "╔════════╤═══════════════════════════════════════════════╗\n";
    std::cout << "║        │                  Время(нс)                    ║\n";
    std::cout << "║        ├───────────────┬───────────────┬───────────────╢\n";
    std::cout << "║ Размер │               │               │               ║\n";
    std::cout << "║        │    Блинная    │     Гномья    │    Быстрая    ║\n";
    std::cout << "║        │               │               │               ║\n";
    std::cout << "╟────────┼───────────────┼───────────────┼───────────────╢\n";
}

void TimeMeasure(int start, int maxLen, int step, int iters, Ordering order)
{
    srandom(time(NULL));

    PrintHeadTime();
    for (int i = start; i <= maxLen + start; i += step)
    {
        std::vector<long long> times(3, 0);
        std::vector<int> vec;
        switch (order)
        {
        case Ordering::Random:
            vec = GetRandomArr(i);
            break;
        case Ordering::Forward:
            vec = GetForwardArr(i);
            break;
        case Ordering::Backward:
            vec = GetBackwardArr(i);
            break;
        }

        for (int j = 0; j < iters; ++j)
        {
            times[0] += MeasureCPUTime(vec, Sort::PancakeSort);
            times[1] += MeasureCPUTime(vec, Sort::GnomeSort);
            times[2] += MeasureCPUTime(vec, Sort::QuickSort);
        }

        double times_0 = times[0] / (double)iters;
        double times_1 = times[1] / (double)iters;
        double times_2 = times[2] / (double)iters;

        std::cout << "║ " << std::setw(6) << i << " │ "
            << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
            << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " │ "
            << std::fixed << std::setprecision(2) << std::setw(13) << times_2 << " ║\n";
    }
    std::cout << "╚════════╧═══════════════╧═══════════════╧═══════════════╝\n";
}