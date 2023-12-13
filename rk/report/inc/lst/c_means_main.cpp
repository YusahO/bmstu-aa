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
