#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "algorithms.h"

namespace Utils
{
    std::vector<std::vector<double>> read_from_file(const std::string &filename)
    {
        std::ifstream f(filename);
        if (!f.is_open())
            throw std::runtime_error("Не удалось открыть файл");

        std::vector<std::vector<double>> points;
        std::string line;
        while (std::getline(f, line))
        {
            std::vector<double> point;
            std::istringstream iss(line);
            double x, y;
            if (iss >> x >> y)
                points.emplace_back(std::vector<double>{x, y});
        }
        f.close();
        return points;
    }

    void print_membership(const Algo::membership_t &matrix)
    {
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            for (size_t j = 0; j < matrix[i].size(); ++j)
            {
                std::cout << std::fixed << std::setprecision(3) << std::setw(6) << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}