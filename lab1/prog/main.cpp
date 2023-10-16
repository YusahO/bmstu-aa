#include <iostream>
#include <string>
#include <limits>

#include "matrix.h"
#include "algorithms.h"
#include "measure.h"

constexpr int MAX_LEN = 1000;
constexpr int MAX_ITER = 10;
constexpr int MAX_REP = 100;

int menu()
{
    std::wcout << L"\n\t\tМеню\n"
        "1. Запуск алгоритмов поиска расстояния Левенштейна:\n"
        "   1) Нерекурсивный Левенштейна;\n"
        "   2) Нерекурсивный Дамерау-Левенштейна;\n"
        "   3) Рекурсивный Дамерау-Левенштейна без кэша;\n"
        "   4) Рекурсивный Дамерау-Левенштейна с кэшем;\n"
        "2. Замерить время для реализованных алгоритмов;\n"
        "0. Выход\n\n"
        "Выберите опцию (0-2): ";

    int choice;
    std::wcin >> choice;
    std::wcout << std::endl;

    return choice;
}

void RunAlgorithms()
{
    std::wstring word1, word2;
    int res;

    std::wcout << L"Введите 1-е слово: ";
    std::wcin >> word1;

    std::wcout << L"Введите 2-е слово: ";
    std::wcin >> word2;
    std::wcout << std::endl;

    std::size_t word1Len = word1.length();
    std::size_t word2Len = word2.length();

    wchar_t shouldPrint = L'n';
    std::wcout << L"Выводить матрицы для итеративных реализаций? [y/N]: ";
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
    std::wcin.get(shouldPrint);
    std::wcout << L'\n';

    shouldPrint = std::towlower(shouldPrint);

    std::wcout << L"Минимальное кол-во операций:\n";
    res = LevNonRec(word1, word2, shouldPrint == L'y');
    std::wcout << L"   1) Нерекурсивный Левенштейна:                " << res << std::endl;

    res = DamLevNonRec(word1, word2, shouldPrint == L'y');
    std::wcout << L"   2) Нерекурсивный Дамерау-Левенштейна:        " << res << std::endl;

    res = DamLevRec(word1, word2, word1Len, word2Len);
    std::wcout << L"   3) Рекурсивный Дамерау-Левенштейна без кэша: " << res << std::endl;

    res = DamLevRecCache(word1, word2);
    std::wcout << L"   4) Рекурсивный Дамерау-Левенштейна с кэшем:  " << res << std::endl;
}

int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int choice;
    while ((choice = menu()))
    {
        if (choice == 1)
        {
            RunAlgorithms();
        }
        else if (choice == 2)
        {
            TimeMeasure(200, 500);
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            std::wcout << L"\033[31mОпция с номером " << choice << L" не поддерживается\033[0m\n"; 
        }
    }

    return 0;
}
