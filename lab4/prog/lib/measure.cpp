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

static Algo::point_vec_t GetRandomPointVec(int n)
{
    Algo::point_vec_t vec(n, std::vector<double>(2));
    for (int i = 0; i < n; ++i)
    {
        vec[i][0] = static_cast<double>(rand()) / RAND_MAX * 5.0;
        vec[i][1] = static_cast<double>(rand()) / RAND_MAX * 3.5;
    }
    return vec;
}

/*
    void c_means(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, double conv_threshold, int max_iters);
*/

double MeasureCPUTime(
    Algo::membership_t &membership,
    Algo::point_vec_t cluster_centers,
    const Algo::point_vec_t &data,
    double m, double conv_threshold, int max_iters,
    ClusterFunc fn)
{
    long long beg, end;

    beg = GetThreadCpuTimeNs();
    fn(membership, cluster_centers, data, m, conv_threshold, max_iters);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

void PrintHeadTime()
{
    std::cout << "╔════════╤═══════════════════════════════╗\n";
    std::cout << "║        │            Время(нс)          ║\n";
    std::cout << "║        ├───────────────┬───────────────╢\n";
    std::cout << "║ Размер │               │               ║\n";
    std::cout << "║        │ Однопоточная  │ Многопоточная ║\n";
    std::cout << "║        │               │               ║\n";
    std::cout << "╟────────┼───────────────┼───────────────╢\n";
}

void TimeMeasure(int start, int maxLen, int step, int iters)
{
    srandom(time(NULL));

    // Algo::c_means(membership, cs, data, 2.0, 1.0, 10);

    const int k = start;
    const double m = 2.0;
    const int max_iters = 40;
    const double conv_threshold = 1.0;

    PrintHeadTime();
    for (int i = start; i <= maxLen + start; i += step)
    {
        std::vector<long long> times(2, 0);

        Algo::point_vec_t data = GetRandomPointVec(i);
        Algo::membership_t membership(i, std::vector<double>(k, 0.0));
        Algo::point_vec_t cluster_centers = GetRandomPointVec(k);

        for (int j = 0; j < iters; ++j)
        {
            times[0] += MeasureCPUTime(membership, cluster_centers, data, m, conv_threshold, max_iters, Algo::c_means);
            times[1] += MeasureCPUTime(membership, cluster_centers, data, m, conv_threshold, max_iters, Algo::c_means_parallel);
        }

        double times_0 = times[0] / (double)iters;
        double times_1 = times[1] / (double)iters;

        std::cout << "║ " << std::setw(6) << i << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " ║\n";
    }
    std::cout << "╚════════╧═══════════════╧═══════════════╝\n";
}