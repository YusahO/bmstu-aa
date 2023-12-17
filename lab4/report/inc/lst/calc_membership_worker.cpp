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
