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
