#pragma once

#include <vector>
#include <iostream>

namespace Algo
{
    using point_vec_t = std::vector<std::vector<double>>;
    using membership_t = std::vector<std::vector<double>>;

    void c_means(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, double conv_threshold, int max_iters);

    void c_means_parallel(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, double conv_threshold, int max_iters, int n_threads);
}

using ConsequentFunc = void (*)(Algo::point_vec_t &,
                                Algo::membership_t &,
                                const Algo::point_vec_t &,
                                double, double, int);

using ParallelFunc = void (*)(Algo::point_vec_t &,
                              Algo::membership_t &,
                              const Algo::point_vec_t &,
                              double, double, int,
                              int );
