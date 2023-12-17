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
    ConsequentFunc fn)
{
    long long beg, end;

    beg = GetThreadCpuTimeNs();
    fn(membership, cluster_centers, data, m, conv_threshold, max_iters);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

double MeasureCPUTime(
    Algo::membership_t &membership,
    Algo::point_vec_t cluster_centers,
    const Algo::point_vec_t &data,
    double m, double conv_threshold, int max_iters,
    ParallelFunc fn, int n_threads)
{
    long long beg, end;

    beg = GetThreadCpuTimeNs();
    fn(membership, cluster_centers, data, m, conv_threshold, max_iters, n_threads);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

void PrintHeadTime()
{
    std::cout << "╔═════════╤═══════════════════════════════╗\n";
    std::cout << "║         │           Время(мкс)          ║\n";
    std::cout << "║  К-во   ├───────────────┬───────────────╢\n";
    std::cout << "║ потоков │ Однопоточная  │ Многопоточная ║\n";
    std::cout << "╟─────────┼───────────────┼───────────────╢\n";
}

void TimeMeasure(int start, int maxLen, int iters)
{
    srandom(time(NULL));

    constexpr const int k = 40;
    constexpr const double m = 2.0;
    constexpr const int max_iters = 1000;
    constexpr const double conv_threshold = 1.0;
    const Algo::point_vec_t data = GetRandomPointVec(10000);
    const Algo::point_vec_t cluster_centers = GetRandomPointVec(k);


    PrintHeadTime();
    for (int i = start; i <= maxLen; i *= 2)
    {
        std::vector<long long> times(2, 0);

        for (int j = 0; j < iters; ++j)
        {
            {
                Algo::point_vec_t loc_cluster_centers = cluster_centers;
                Algo::membership_t membership(data.size(), std::vector<double>(k, 0.0));
                times[0] += MeasureCPUTime(membership, loc_cluster_centers, data, m, conv_threshold, max_iters, Algo::c_means);
            }
            {
                Algo::point_vec_t loc_cluster_centers = cluster_centers;
                Algo::membership_t membership(data.size(), std::vector<double>(k, 0.0));
                times[1] += MeasureCPUTime(membership, loc_cluster_centers, data, m, conv_threshold, max_iters, Algo::c_means_parallel, i);
            }
        }

        double times_0 = times[0] / (double)iters / 1000.0;
        double times_1 = times[1] / (double)iters / 1000.0;

        std::cout << "║ " << std::setw(7) << i << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " ║\n";
    }
    std::cout << "╚═════════╧═══════════════╧═══════════════╝\n";
}