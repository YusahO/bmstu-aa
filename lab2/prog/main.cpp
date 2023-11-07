#include <iostream>
#include <string>
#include <limits>

#include "matrix.h"
#include "algorithms.h"
#include "measure.h"

int menu()
{
    std::wcout << L"\n\t\tМеню\n"
        "1. Стандартное умножение матриц\n"
        "2. Умножение алгоритмом Винограда\n"
        "3. Умножение оптимизированным алгоритмом Винограда\n"
        "4. Замерить время для реализованных алгоритмов.\n"
        "0. Выход\n\n"
        "Выберите опцию (0-4): ";

    int choice;
    std::wcin >> choice;
    std::wcout << std::endl;

    return choice;
}

int main()
{
    int choice = 0;
    while ((choice = menu()))
    {
        
    }
    return 0;
}
