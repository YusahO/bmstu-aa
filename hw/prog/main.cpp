#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

void c_means_clustering(std::vector<std::vector<double>> &cluster_centers, // -1
    std::vector<std::vector<double>> &membership, // -2
    const std::vector<std::vector<double>> &data, // -3
    double m /* -4 */, double convergenceThreshold /* -5 */, double maxIterations /* -6 */)
{
    int iterations = 0;                                                                  // (1)
    double delta = convergenceThreshold + 1.0;                                           // (2)
    while (iterations < maxIterations && delta > convergenceThreshold)                   // (3)
    {
        for (size_t i = 0; i < data.size(); ++i)                                         // (4)
        {
            for (size_t j = 0; j < cluster_centers.size(); ++j)                          // (5)
            {
                double sum = 0.0;                                                        // (6)
                double dist1 = sqrt(pow(data[i][0] - cluster_centers[j][0], 2) +
                                    pow(data[i][1] - cluster_centers[j][1], 2));         // (7)
                for (size_t k = 0; k < cluster_centers.size(); ++k)                      // (8)
                {
                    double dist2 = sqrt(pow(data[i][0] - cluster_centers[k][0], 2) +
                                        pow(data[i][1] - cluster_centers[k][1], 2));     // (9)
                    sum += pow(dist1 / dist2, 2.0 / (m - 1.0));                          // (10)
                }
                membership[i][j] = 1.0 / sum;                                            // (11)
            }
        }
        for (size_t j = 0; j < cluster_centers.size(); ++j)                              // (12)
        {
            double numeratorX = 0.0;                                                     // (13)
            double numeratorY = 0.0;                                                     // (14)
            double denominator = 0.0;                                                    // (15)
            for (size_t i = 0; i < data.size(); ++i)                                     // (16)
            {
                double membershipPowM = pow(membership[i][j], m);                        // (17)
                numeratorX += membershipPowM * data[i][0];                               // (18)
                numeratorY += membershipPowM * data[i][1];                               // (19)
                denominator += membershipPowM;                                           // (20)
            }
            cluster_centers[j] = { numeratorX / denominator, numeratorY / denominator }; // (21)
        }
        std::vector<std::vector<double>> old_cluster_centers = cluster_centers;
        delta = 0.0;
        for (size_t i = 0; i < cluster_centers.size(); ++i)
        {
            delta = sqrt(pow(data[i][0] - old_cluster_centers[i][0], 2) +
                         pow(data[i][1] - cluster_centers[i][1], 2));
        }
        ++iterations;
    }
}

int main()
{
    int k = 1; // Number of clusters
    double m = 2.0; // Fuzziness parameter
    int maxIterations = 1;
    double convergenceThreshold = 0.1;

    std::vector<std::vector<double>> data = { {5.1, 2.5}, {1.4, 0.2} };

    std::vector<std::vector<double>> cluster_centers(k, std::vector<double>(2));
    for (int i = 0; i < k; ++i)
    {
        cluster_centers[i][0] = static_cast<double>(rand()) / RAND_MAX * 5.0;
        cluster_centers[i][1] = static_cast<double>(rand()) / RAND_MAX * 3.5;
    }

    std::vector<std::vector<double>> membership(data.size(), std::vector<double>(k, 0.0));

    c_means_clustering(cluster_centers, membership, data, m, convergenceThreshold, maxIterations);

    std::cout << "Final Cluster Centers:" << std::endl;
    for (size_t i = 0; i < cluster_centers.size(); ++i)
    {
        for (size_t j = 0; j < cluster_centers[i].size(); ++j)
        {
            std::cout << cluster_centers[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}