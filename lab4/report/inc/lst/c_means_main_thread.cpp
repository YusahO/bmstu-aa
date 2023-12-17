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
