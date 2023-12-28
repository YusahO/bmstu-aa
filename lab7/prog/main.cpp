#include <iostream>
#include "algorithms.h"
#include "measure.h"

int menu()
{
    std::cout << "\n\t\tМеню\n"
                 "1. Выполнить поиск элемента алгоритмом бинарного поиска\n"
                 "    a) с двумя сравнениями с медианным элементом;\n"
                 "    б) с одним сравнением с медианным элементом.\n"
                 "2. Подсчитать количество сравнений при выполнении поиска элементов.\n"
                 "0. Выход.\n\n"
                 "Выберите опцию (0-2): ";

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
            int sz, x;
            std::cout << "Введите к-во элементов массива: ";
            std::cin >> sz;
            std::vector<int> vec(sz);

            std::cout << "Введите элементы массива (в порядке возрастания): ";
            for (int i = 0; i < sz; ++i)
            {
                std::cin >> vec[i];
            }

            std::cout << "Введите искомый элемент: ";
            std::cin >> x;

            int res_01 = Algs::bin_search_one_comp(vec, x);
            int res_02 = Algs::bin_search_two_comp(vec, x);

            if (res_01 == -1 || res_02 == -1)
            {
                std::cout << "Элемент не найден.\n";
            }
            else
            {
                std::cout << "Индекс найденного элемента (2 сравнения): " << res_02 << "\n";
                std::cout << "Индекс найденного элемента (1 сравнение): " << res_01 << "\n";
            }
        }
        else if (choice == 2)
        {
            CompMeasure(0);
            CompMeasure(1);
        }
    }
    return 0;
}