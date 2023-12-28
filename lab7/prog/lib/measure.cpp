#include "measure.h"

#include "pipeline.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <array>

std::vector<int> GenVector(int sz)
{
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; ++i)
        vec[i] = i;
    return vec;
}

void CompMeasure(int shift)
{
    srandom(time(NULL));

    std::array<int, 5> Ns = {512, 1024, 2048, 4096, 8192};
    for (int N : Ns)
    {
        // Algs::reset_cntr();
        // {
        //     std::vector<int> vec = GenVector(N + shift);
        //     int best_case = vec[N / 2];
        //     Algs::bin_search_one_comp(vec, best_case);
        //     Algs::bin_search_two_comp(vec, best_case);
        //     auto [o, t] = Algs::get_comp_amt();
        //     std::cout << N+shift << " " << o << " " << t << "\n";
        // }
        Algs::reset_cntr();
        {
            std::vector<int> vec = GenVector(N + shift);
            int best_case = vec[N-1];
            Algs::bin_search_one_comp(vec, best_case);
            Algs::bin_search_two_comp(vec, best_case);
            auto [o, t] = Algs::get_comp_amt();
            std::cout << N+shift << " " << o << " " << t << "\n";
        }
        // Algs::reset_cntr();
        // {
        //     std::vector<int> vec = GenVector(N + shift);
        //     int worst_case = N + 1;
        //     Algs::bin_search_one_comp(vec, worst_case);
        //     Algs::bin_search_two_comp(vec, worst_case);
        //     auto [o, t] = Algs::get_comp_amt();
        //     std::cout << N+shift << " " << o << " " << t << "\n";
        // }
        std::cout << "\n";
    }
}