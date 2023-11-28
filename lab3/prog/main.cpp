#include <iostream>

#include <iostream>
#include <string>
#include <cstdlib>

#include "algorithms.h"
#include "measure.h"

namespace std
{
    ostream &operator<<(ostream &os, const vector<int> &arr)
    {
        os << "[ ";
        for (const int v : arr)
            cout << v << " ";
        os << "]";
        return os;
    }
}

int menu()
{
    std::cout << "\n\t\tМеню\n"
        "1. Сортировка массива с помощью:\n"
        "   a) блинной сортировки;\n"
        "   б) гномьей сортировки.\n"
        "   в) быстрой сортировки;\n"
        "2. Произвести замеры по времени реализуемых алгоритмов.\n"
        "0. Выход.\n\n"
        "Выберите опцию (0-2): ";

    int choice;
    std::cin >> choice;
    std::cout << std::endl;

    return choice;
}

void RunSorts(std::vector<int> &arr)
{
    if (arr.size() == 0)
    {
        std::cout << "Длина массива, равна 0, не является допустимой";
        return;
    }

    std::vector<int> sortedArr = arr;
    Sort::PancakeSort(sortedArr);
    std::cout << "Блинная сортировка: " << sortedArr << "\n";

    sortedArr = arr;
    Sort::GnomeSort(sortedArr);
    std::cout << "Гномья сортировка:  " << sortedArr << "\n";

    sortedArr = arr;
    Sort::QuickSort(sortedArr, 0, sortedArr.size() - 1);
    std::cout << "Быстрая сортировка: " << sortedArr << "\n";
}

int main()
{
    int choice = 0;
    while ((choice = menu()))
    {
        if (choice == 1)
        {
            std::vector<int> arr;
            int sz = 0;
            std::cout << "Введите размер сортируемого массива: ";
            std::cin >> sz;
            arr.resize(sz);

            std::cout << "Введите сам массив: ";
            for (int i = 0; i < sz; ++i)
                std::cin >> arr[i];
            std::cout << "\n";

            RunSorts(arr);
        }
        if (choice == 2)
        {
            std::cout << "Сортировка неупорядоченных массивов:\n";
            TimeMeasure(1, 1000, 100, 100, Ordering::Random);

            std::cout << "Сортировка массивов, упорядоченных по возрастанию:\n";
            TimeMeasure(1, 1000, 100, 100, Ordering::Forward);

            std::cout << "Сортировка массивов, упорядоченных по убыванию:\n";
            TimeMeasure(1, 1000, 100, 100, Ordering::Backward);
        }
    }
    return 0;
}