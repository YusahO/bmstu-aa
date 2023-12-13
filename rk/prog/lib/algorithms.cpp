#include "algorithms.h"

#include <cmath>
#include <thread>

namespace Algo
{
    static void mt_calc_membership(
        membership_t &membership,
        const point_vec_t &data, point_vec_t &cluster_centers, double m,
        int rows_n_thread, int cols_n_thread)
    {
        std::vector<std::thread> threads;

        int data_step = ceil(float(data.size()) / float(rows_n_thread));
        int c_step = ceil(float(cluster_centers.size()) / float(cols_n_thread));
        
        for (size_t data_from = 0; data_from < data.size(); data_from += data_step)
        {
            for (size_t c_from = 0; c_from < cluster_centers.size(); c_from += c_step)
            {
                int data_to = std::min<int>(data_from + data_step, data.size());
                int center_to = std::min<int>(c_from + c_step, cluster_centers.size());
                threads.emplace_back(
                    [ &, data_from, data_to, c_from, center_to ]
                    {
                        for (int i = data_from; i < data_to; ++i)
                        {
                            for (int j = c_from; j < center_to; ++j)
                            {
                                double sum = 0.0;
                                double dist1 = sqrt(
                                    pow(data[i][0] - cluster_centers[j][0], 2) +
                                    pow(data[i][1] - cluster_centers[j][1], 2)
                                );
                                for (size_t k = 0; k < cluster_centers.size(); ++k)
                                {
                                    double dist2 = sqrt(
                                        pow(data[i][0] - cluster_centers[k][0], 2) +
                                        pow(data[i][1] - cluster_centers[k][1], 2)
                                    );
                                    sum += pow(dist1 / dist2, 2.0 / (m - 1.0));
                                }
                                membership[i][j] = 1.0 / sum;
                            }
                        }
                    });
            }
        }
        for (auto &thr : threads)
            thr.join();
    }

    static void mt_recalc_clustercenters(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, int n_threads)
    {
        std::vector<std::thread> threads;
        int cltr_step = ceil(float(cluster_centers.size()) / float(n_threads));
        for (size_t cltr_beg = 0; cltr_beg < cluster_centers.size(); cltr_beg += cltr_step)
        {
            int cltr_end = std::min<int>(cltr_beg + cltr_step, cluster_centers.size());
            threads.emplace_back(
                [ &, cltr_beg, cltr_end ]
                {
                    for (int j = cltr_beg; j < cltr_end; ++j)
                    {
                        double x_nom = 0.0, y_nom = 0.0, denom = 0.0;
                        for (size_t i = 0; i < data.size(); ++i)
                        {
                            double membership_pow_m = pow(membership[i][j], m);
                            x_nom += membership_pow_m * data[i][0];
                            y_nom += membership_pow_m * data[i][1];
                            denom += membership_pow_m;
                        }
                        cluster_centers[j] = { x_nom / denom, y_nom / denom };
                    }
                }
            );
        }
        for (auto &thr : threads)
            thr.join();
    }

    static double mt_calc_distance(
        point_vec_t &cluster_centers,
        point_vec_t &old_cluster_centers,
        int n_threads)
    {
        std::vector<std::thread> threads;
        std::vector<double> thr_results(n_threads);
        int cltr_step = ceil(float(cluster_centers.size()) / float(n_threads));
        for (size_t cltr_beg = 0; cltr_beg < cluster_centers.size(); cltr_beg += cltr_step)
        {
            int cltr_end = std::min<int>(cltr_beg + cltr_step, cluster_centers.size());
            int ires = --n_threads;
            threads.emplace_back(
                [ &, cltr_beg, cltr_end, ires ]
                {
                    double delta = 0;
                    for (int i = cltr_beg; i < cltr_end; ++i)
                    {
                        double distance = sqrt(
                            pow(old_cluster_centers[i][0] - cluster_centers[i][0], 2) +
                            pow(old_cluster_centers[i][1] - cluster_centers[i][1], 2)
                        );
                        if (distance > delta)
                            delta = distance;
                    }
                    thr_results[ires] = delta;
                }
            );
        }
        for (auto &thr : threads)
        {
            thr.join();
        }
        double delta = 0;
        for (auto &distance : thr_results)
        {
            if (distance > delta)
                delta = distance;
        }
        return delta;
    }

    void c_means_parallel(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, double conv_threshold, int max_iters)
    {
        int iters = 0;
        double delta = conv_threshold + 1.0;
        while (iters < max_iters && delta > conv_threshold)
        {
            std::vector<std::thread> threads;
            mt_calc_membership(membership, data, cluster_centers, m, 2, 2);

            auto old_cluster_centers = cluster_centers;
            mt_recalc_clustercenters(membership, cluster_centers, data, m, 2);
            delta = mt_calc_distance(cluster_centers, old_cluster_centers, 2);
            ++iters;
        }
    }
}
