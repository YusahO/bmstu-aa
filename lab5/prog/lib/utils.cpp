#include "utils.h"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace utils
{
    int get_request_count()
    {
        int req_cnt;
        std::cout << "Введите количество заявок: ";
        std::cin >> req_cnt;
        return req_cnt;
    }
    std::tuple<int, double, double, int> get_clust_params()
    {
        int k, max_iters;
        double m, conv_theshold;

        std::cout << "Введите количество кластеров: ";
        std::cin >> k;
        std::cout << "Введите показатель нечеткости: ";
        std::cin >> m;
        std::cout << "Введите порог сходимости: ";
        std::cin >> conv_theshold;
        std::cout << "Введите максимальное количество итераций: ";
        std::cin >> max_iters;

        return {k, m, conv_theshold, max_iters};
    }

    std::vector<std::string> pick_datasets(int req_cnt)
    {
        auto dataset_path = fs::current_path().parent_path() / "prog" / "descriptions";
        std::vector<std::string> files;
        files.reserve(10);
        for (const auto &entry : fs::directory_iterator(dataset_path))
            files.emplace_back(entry.path().c_str());

        if (files.empty())
            return {};

        std::cout << "Выберите файлы описания датасета:\n";
        for (size_t i = 0; i < files.size(); ++i)
        {
            std::cout << "    " << i + 1 << ". "
                      << "\"" << files[i] << "\""
                      << "\n";
        }
        std::cout << "Номера файлов (0 для выхода): ";
        std::vector<std::string> selected(req_cnt, files[0]);
        size_t fileno = 1;
        for (size_t i = 0; fileno && i < selected.size(); ++i)
        {
            std::cin >> fileno;
            if (fileno != 0 && fileno <= files.size())
                selected[i] = files[fileno - 1];
        }
        return selected;
    }
}
