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
