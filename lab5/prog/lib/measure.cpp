#include "measure.h"

#include "pipeline.h"

#include <vector>
#include <iostream>
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

double MeasureCPUTime(int req_cnt, const std::vector<std::string> &datasets, ProcFn fn)
{
    std::tuple cls_params = {5, 2.0, 1.0, 1000};

    long long beg, end;
    beg = GetThreadCpuTimeNs();
    fn(req_cnt, datasets, cls_params, false);
    end = GetThreadCpuTimeNs();

    return (double)(end - beg);
}

void PrintHead()
{
    std::cout << "╔═════════╤═══════════════════════════════╗\n";
    std::cout << "║         │           Время(мкс)          ║\n";
    std::cout << "║  К-во   ├───────────────┬───────────────╢\n";
    std::cout << "║  заявок │   Линейная    │  Конвейерная  ║\n";
    std::cout << "╟─────────┼───────────────┼───────────────╢\n";
}

void TimeMeasureRequests(int start, int max_rcnt, int step, int iters)
{
    srandom(time(NULL));

    PrintHead();
    for (int i = start; i <= max_rcnt; i += step)
    {
        std::vector<long long> times(2, 0);
        std::vector<std::string> datasets(i, "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_02.txt");
        for (int r = 0; r < iters; ++r)
        {
            times[0] += MeasureCPUTime(i, datasets, consequent);
            times[1] += MeasureCPUTime(i, datasets, concurrent);
        }

        double times_0 = times[0] / (double)iters / 1000.0;
        double times_1 = times[1] / (double)iters / 1000.0;
        std::cout << "║ " << std::setw(7) << i << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " ║\n";
    }
    std::cout << "╚═════════╧═══════════════╧═══════════════╝\n";
}

void PrintHeadFiles()
{
    std::cout << "╔═════════╤═══════════════════════════════╗\n";
    std::cout << "║         │           Время(мкс)          ║\n";
    std::cout << "║  К-во   ├───────────────┬───────────────╢\n";
    std::cout << "║  файлов │   Линейная    │  Конвейерная  ║\n";
    std::cout << "╟─────────┼───────────────┼───────────────╢\n";
}

void TimeMeasureFiles(int iters)
{
    srandom(time(NULL));

    const std::vector<std::string> files = {
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_01.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_02.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_03.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_04.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_05.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_06.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_07.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_08.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_09.txt",
        "/home/daria/Документы/bmstu-aa/lab5/prog/descriptions/ds_10.txt"
    };

    PrintHeadFiles();
    int fcnt = 0;
    for (const auto &file : files)
    {
        std::vector<long long> times(2, 0);
        std::vector<std::string> datasets(10, file);
        for (int r = 0; r < iters; ++r)
        {
            times[0] += MeasureCPUTime(10, datasets, consequent);
            times[1] += MeasureCPUTime(10, datasets, concurrent);
        }

        double times_0 = times[0] / (double)iters / 1000.0;
        double times_1 = times[1] / (double)iters / 1000.0;
        std::cout << "║ " << std::setw(7) << ++fcnt << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_0 << " │ "
                  << std::fixed << std::setprecision(2) << std::setw(13) << times_1 << " ║\n";
    }
    std::cout << "╚═════════╧═══════════════╧═══════════════╝\n";
}