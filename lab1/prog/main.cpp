#include <iostream>
#include <string>

#include "matrix.h"
#include "algorithms.h"
#include "measure.h"

constexpr int MAX_LEN = 1000;
constexpr int MAX_ITER = 10;
constexpr int MAX_REP = 100;

enum class Options
{
    Quit = 0,
    RunAlgos,
    Measure
};

int menu()
{
    int choice;

    std::wcout << L"\n\t\tМеню\n"
        "1. Запуск алгоритмов поиска расстояния Левенштейна:\n"
        "   1) Нерекурсивный Левенштейна;\n"
        "   2) Нерекурсивный Дамерау-Левенштейна;\n"
        "   3) Рекурсивный Дамерау-Левенштейна без кэша;\n"
        "   4) Рекурсивный Дамерау-Левенштейна с кэшем;\n"
        "2. Замерить время для реализованных алгоритмов;\n"
        "0. Выход\n\n"
        "Выберите пункт (0-2): ";

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

    std::wcout << L"Минимальное кол-во операций:\n";
    res = LevNonRec(word1, word2, true);
    std::wcout << L"   1) Нерекурсивный Левенштейна:                " << res << std::endl;

    res = DamLevNonRec(word1, word2, true);
    std::wcout << L"   2) Нерекурсивный Дамерау-Левенштейна:        " << res << std::endl;

    res = DamLevRec(word1, word2, word1Len, word2Len);
    std::wcout << L"   3) Рекурсивный Дамерау-Левенштейна без кэша: " << res << std::endl;

    int **dp = Matrix::Allocate(DP_MatrixSize, DP_MatrixSize, -1);
    res = DamLevRecCache(word1, word2, word1Len, word2Len, dp);
    std::wcout << L"   4) Рекурсивный Дамерау-Левенштейна с кэшем:  " << res << std::endl;
    Matrix::Free(dp, DP_MatrixSize);
}

int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int choice;
    do
    {
        switch (static_cast<Options>(choice))
        {
        case Options::RunAlgos:
            RunAlgorithms();
            break;
        case Options::Measure:
            TimeMeasure(200, 500);
            break;
        case Options::Quit:
            choice = 0;
            break;
        default:
            break;
        }
    } while (choice && (choice = menu()));

    return 0;
}