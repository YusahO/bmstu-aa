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
