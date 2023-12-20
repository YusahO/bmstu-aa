#include "algorithms.h"

#include <cmath>
#include <thread>

namespace Algo
{
    void c_means(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, double conv_threshold, int max_iters)
    {
        int iters = 0;
        double delta = conv_threshold + 1.0;
        while (iters < max_iters && delta > conv_threshold)
        {
            for (size_t i = 0; i < data.size(); ++i)
            {
                for (size_t j = 0; j < cluster_centers.size(); ++j)
                {
                    double sum = 0.0;
                    double dist1 = sqrt(pow(data[i][0] - cluster_centers[j][0], 2) +
                                        pow(data[i][1] - cluster_centers[j][1], 2));
                    for (size_t k = 0; k < cluster_centers.size(); ++k)
                    {
                        double dist2 = sqrt(pow(data[i][0] - cluster_centers[k][0], 2) +
                                            pow(data[i][1] - cluster_centers[k][1], 2));
                        sum += pow(dist1 / dist2, 2.0 / (m - 1.0));
                    }
                    membership[i][j] = 1.0 / sum;
                }
            }
            auto old_cluster_centers = cluster_centers;
            for (size_t j = 0; j < cluster_centers.size(); ++j)
            {
                double x_nom = 0.0, y_nom = 0.0, denom = 0.0;
                for (size_t i = 0; i < data.size(); ++i)
                {
                    double membership_pow_m = pow(membership[i][j], m);
                    x_nom += membership_pow_m * data[i][0];
                    y_nom += membership_pow_m * data[i][1];
                    denom += membership_pow_m;
                }
                cluster_centers[j] = {x_nom / denom, y_nom / denom};
            }
            delta = 0.0;
            for (size_t i = 0; i < cluster_centers.size(); ++i)
            {
                double distance = sqrt(pow(old_cluster_centers[i][0] - cluster_centers[i][0], 2) +
                                       pow(old_cluster_centers[i][1] - cluster_centers[i][1], 2));
                if (distance > delta)
                    delta = distance;
            }
            ++iters;
        }
    }

    static void calc_membership_worker(
        const point_vec_t &data,
        const point_vec_t &cluster_centers,
        membership_t &membership,
        int data_from, int data_to, double m)
    {
        for (int i = data_from; i < data_to; ++i)
        {
            for (size_t j = 0; j < cluster_centers.size(); ++j)
            {
                double sum = 0.0;
                double dist1 = sqrt(
                    pow(data[i][0] - cluster_centers[j][0], 2) +
                    pow(data[i][1] - cluster_centers[j][1], 2));
                for (size_t k = 0; k < cluster_centers.size(); ++k)
                {
                    double dist2 = sqrt(
                        pow(data[i][0] - cluster_centers[k][0], 2) +
                        pow(data[i][1] - cluster_centers[k][1], 2));
                    sum += pow(dist1 / dist2, 2.0 / (m - 1.0));
                }
                membership[i][j] = 1.0 / sum;
            }
        }
    }

    static void calc_membership(
        membership_t &membership,
        const point_vec_t &data, point_vec_t &cluster_centers, double m,
        int n_threads)
    {
        std::vector<std::thread> threads;

        int data_step = ceil(float(data.size()) / float(n_threads));
        for (size_t data_from = 0; data_from < data.size(); data_from += data_step)
        {
            int data_to = std::min<int>(data_from + data_step, data.size());
            threads.emplace_back(
                calc_membership_worker,
                std::ref(data),
                std::ref(cluster_centers),
                std::ref(membership),
                data_from, data_to, m);
        }
        for (auto &thr : threads)
        {
            if (thr.joinable())
                thr.join();
        }
    }

    void c_means_parallel(
        membership_t &membership, point_vec_t &cluster_centers,
        const point_vec_t &data,
        double m, double conv_threshold, int max_iters,
        int n_threads)
    {
        int iters = 0;
        double delta = conv_threshold + 1.0;
        while (iters < max_iters && delta > conv_threshold)
        {
            std::vector<std::thread> threads;
            calc_membership(membership, data, cluster_centers, m, n_threads);

            auto old_cluster_centers = cluster_centers;
            for (size_t j = 0; j < cluster_centers.size(); ++j)
            {
                double x_nom = 0.0, y_nom = 0.0, denom = 0.0;
                for (size_t i = 0; i < data.size(); ++i)
                {
                    double membership_pow_m = pow(membership[i][j], m);
                    x_nom += membership_pow_m * data[i][0];
                    y_nom += membership_pow_m * data[i][1];
                    denom += membership_pow_m;
                }
                cluster_centers[j] = {x_nom / denom, y_nom / denom};
            }
            delta = 0.0;
            for (size_t i = 0; i < cluster_centers.size(); ++i)
            {
                double distance = sqrt(pow(old_cluster_centers[i][0] - cluster_centers[i][0], 2) +
                                       pow(old_cluster_centers[i][1] - cluster_centers[i][1], 2));
                if (distance > delta)
                    delta = distance;
            }
            ++iters;
        }
    }
}