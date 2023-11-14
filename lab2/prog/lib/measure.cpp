#include "measure.h"

#include <vector>
#include <iomanip>

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

double MeasureCPUTime(const Matrix &m1, const Matrix &m2, MatMulFunc fn)
{
    long long beg, end;

    beg = GetThreadCpuTimeNs();
    Matrix res = fn(m1, m2);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

void PrintHead()
{
    std::cout << "╔════════╤═══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║        │                         Время(нс)                             ║\n";
    std::cout << "║        ├───────────────┬───────────────────────────────┬───────────────╢\n";
    std::cout << "║ Размер │               │           Винограда           │               ║\n";
    std::cout << "║        │    Обычное    ├───────────────┬───────────────┤   Штрассена   ║\n";
    std::cout << "║        │               │  Неоптимизир. │   Оптимизир.  │               ║\n";
    std::cout << "╟────────┼───────────────┼───────────────┼───────────────┼───────────────╢\n";

}

void TimeMeasure(int start, int maxLen, int iters)
{
    srandom(time(NULL));

    const int step = 10;
    start = start == 0 ? step : start;

    PrintHead();
    for (int i = start; i <= maxLen + start; )
    {
        std::vector<long long> times( 4, 0 ); 

        Matrix m1(i, i);
        Matrix m2(i, i);
        m1.fillRandom();
        m2.fillRandom();

        for (int j = 0; j < iters; ++j)
        {
            times[0] += MeasureCPUTime(m1, m2, Multiply::Common);
            times[1] += MeasureCPUTime(m1, m2, Multiply::Winograd);
            times[2] += MeasureCPUTime(m1, m2, Multiply::WinogradOpt);

            if (start == 2)
                times[3] += MeasureCPUTime(m1, m2, Multiply::Strassen);
        }

        double times_0 = times[0] / (double)iters;
        double times_1 = times[1] / (double)iters;
        double times_2 = times[2] / (double)iters;

        std::cout << "║ " << std::setw(6) << i << " │ "
        << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
        << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " │ "
        << std::fixed << std::setprecision(2) << std::setw(13) << times_2 << " │ ";

        if (start == 2)
        {
            double times_3 = times[3] / (double)iters;
            std::cout << std::fixed << std::setprecision(2) << std::setw(13) << times_3 << " ║\n";
            i *= 2;
        }
        else
        {
            i += step;
            std::cout << std::setw(13) << '-' << " ║\n";
        }
    }
    std::cout << "╚════════╧═══════════════╧═══════════════╧═══════════════╧═══════════════╝\n";
}
