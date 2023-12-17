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
        thr.join();
}
