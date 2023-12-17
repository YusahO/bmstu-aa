#include <thread>
#include <iostream>

void func(int &res, int a, int b)
{
    res = a + b;
}

int main()
{
    int res;
    std::thread th(func, std::ref(res), 10, 20);
    th.join();
    std::cout << res << "\n";
    return 0;
}

