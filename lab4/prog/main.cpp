#include <iostream>

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "algorithms.h"
#include "utils.h"
#include "measure.h"

constexpr const char *s_Filename = "/home/daria/Документы/bmstu-AA/lab4/prog/data/points.txt";

namespace std
{
    template <typename T>
    ostream &operator<<(ostream &os, const vector<T> &arr)
    {
        os << "[ ";
        for (const T &v : arr)
            cout << v << " ";
        os << "]";
        return os;
    }
}

int menu()
{
    std::cout << "\n\t\tМеню\n"
                 "1. Кластеризация методом c-средних:\n"
                 "    a) однопоточная;\n"
                 "    б) многопоточная.\n"
                 "2. Редактировать файл, содержащий множество точек.\n"
                 "3. Произвести замеры по времени реализуемых алгоритмов.\n"
                 "0. Выход.\n\n"
                 "Выберите опцию (0-3): ";

    int choice;
    std::cin >> choice;
    std::cout << std::endl;

    return choice;
}

int main()
{
    int choice = 0;
    while ((choice = menu()))
    {
        if (choice == 1)
        {
            auto data = Utils::read_from_file(s_Filename);
            int k;
            std::cout << "Введите число кластеров (1-" << data.size() << "): ";
            std::cin >> k;

            float m, conv_threshold;
            int max_iters;
            std::cout << "Введите значение показателя нечеткости: ";
            std::cin >> m;
            std::cout << "Введите значение порога сходимости: ";
            std::cin >> conv_threshold;
            std::cout << "Введите максимальное к-во итераций: ";
            std::cin >> max_iters;

            int n_threads;
            std::cout << "Введите число дополнительных потоков (для многопоточной версии): ";
            std::cin >> n_threads;

            Algo::point_vec_t cluster_centers(k, std::vector<double>(2));

            for (int i = 0; i < k; ++i)
            {
                cluster_centers[i][0] = static_cast<double>(rand()) / RAND_MAX * 5.0;
                cluster_centers[i][1] = static_cast<double>(rand()) / RAND_MAX * 3.5;
            }
            {
                Algo::membership_t membership(data.size(), std::vector<double>(k, 0.0));
                Algo::point_vec_t cs = cluster_centers;

                Algo::c_means(membership, cs, data, m, conv_threshold, max_iters);

                std::cout << "Матрица принадлежности\n";
                Utils::print_membership(membership);
                std::cout << "Центроиды кластеров: " << cs << "\n";
            }

            {
                Algo::membership_t membership(data.size(), std::vector<double>(k, 0.0));
                Algo::point_vec_t cs = cluster_centers;

                Algo::c_means_parallel(membership, cs, data, m, conv_threshold, max_iters, n_threads);

                std::cout << "Матрица принадлежности\n";
                Utils::print_membership(membership);
                std::cout << "Центроиды кластеров: " << cs << "\n";
            }
        }
        else if (choice == 2)
        {
            std::system(("kwrite " + std::string(s_Filename)).c_str());
        }
        else if (choice == 3)
        {
            // TimeMeasureThreads(1, 16 * 8, 20);
            TimeMeasureLength(5000, 30000, 5000, 10);
        }
    }
    return 0;
}