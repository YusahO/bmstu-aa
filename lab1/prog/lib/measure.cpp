#include "measure.h"

#include <vector>
#include <iomanip>

std::wstring GenerateWord(unsigned long len)
{
    static std::wstring symbols = L"0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
        "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    std::wstring word;

    for (std::size_t i = 0; i < len; ++i)
        word.push_back(symbols[rand() % (symbols.length() - 1)]);

    return word;
}

static long long GetThreadCpuTimeNs()
{
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t))
    {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double MeasureCPUTime(const std::wstring &word1, const std::wstring &word2, NonRecursiveFunc fn)
{
    long long beg, end;

    beg = GetThreadCpuTimeNs();
    int res = fn(word1, word2, false);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

double MeasureCPUTime(const std::wstring &word1, const std::wstring &word2, RecursiveFunc fn)
{
    int len1 = word1.length();
    int len2 = word2.length();

    long long beg, end;

    beg = GetThreadCpuTimeNs();
    int res = fn(word1, word2, len1, len2);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

double MeasureCPUTime(const std::wstring &word1, const std::wstring &word2, RecursiveCacheFunc fn)
{
    int len1 = word1.length();
    int len2 = word2.length();

    int **dp = Matrix::Allocate(DP_MatrixSize, DP_MatrixSize);

    long long beg, end;

    beg = GetThreadCpuTimeNs();
    int res = fn(word1, word2, len1, len2, dp);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

void PrintHead()
{
    std::wcout << L"╔═══════╤═══════════════════════════════════════════════════════════════╗\n";
    std::wcout << L"║       │                          Время(нс)                            ║\n";
    std::wcout << L"║       ├───────────────┬───────────────────────────────────────────────╢\n";
    std::wcout << L"║       │               │                 Дамерау-Левенштейн            ║\n";
    std::wcout << L"║ Длина │  Левенштейн   ├───────────────┬───────────────────────────────╢\n";
    std::wcout << L"║(симв.)│  Итеративный  │               │          Рекурсивный          ║\n";
    std::wcout << L"║       │               │  Итеративный  ├───────────────┬───────────────╢\n";
    std::wcout << L"║       │               │               │   Без кэша    │    С кэшем    ║\n";
    std::wcout << L"╟───────┼───────────────┼───────────────┼───────────────┼───────────────╢\n";

}

void TimeMeasure(int maxLen, int iters)
{
    PrintHead();
    srandom(time(NULL));

    for (int i = 1; i <= maxLen;)
    {
        std::vector<long long> times( 4, 0 );

        std::wstring word1 = GenerateWord(i);
        std::wstring word2 = GenerateWord(i);   

        for (int j = 0; j < iters; ++j)
        {
            times[0] += MeasureCPUTime(word1, word2, LevNonRec);
            times[1] += MeasureCPUTime(word1, word2, DamLevNonRec);

            if (i < 11)
            {
                times[2] += MeasureCPUTime(word1, word2, DamLevRec);
                times[3] += MeasureCPUTime(word1, word2, DamLevRecCache);
            }
        }

        double times_0 = times[0] / (double)iters;
        double times_1 = times[1] / (double)iters;
        double times_2 = times[2] / (double)iters;
        double times_3 = times[3] / (double)iters;

        std::wcout << L"║ " << std::setw(5) << i << L" │ "
        << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << L" │ "
        << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << L" │ ";

        if (i < 11)
        {
            std::wcout << std::fixed << std::setprecision(2) << std::setw(13) << times_2 << L" │ "
            << std::fixed << std::setprecision(2) << std::setw(13) << times_3 << L" ║\n";
        }
        else
        {
            std::wcout << std::fixed << std::setprecision(2) << std::setw(13) << '-' << L" │ "
            << std::fixed << std::setprecision(2) << std::setw(13) << '-' << L" ║\n";
        }

        if (i < 10)
            ++i;
        else if (i < 100)
            i += 10;
        else
            i += 100;
    }

    std::wcout << L"╚═══════╧═══════════════╧═══════════════╧═══════════════╧═══════════════╝\n";
}