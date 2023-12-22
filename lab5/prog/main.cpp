#include "pipeline.h"

int menu()
{
    std::cout << "\n\t\tМеню\n"
                 "1. Запустить последовательную обработку датасета файлов MIDI.\n"
                 "2. Запустить конвейерную обработку датасета файлов MIDI.\n"
                 "3. Произвести замеры по времени реализуемых алгоритмов.\n"
                 "0. Выход.\n\n"
                 "Выберите опцию (0-3): ";

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
            consequent();
        }
        else if (choice == 2)
        {
            concurrent();
        }
        else if (choice == 3)
        {
        }
    }
    return 0;
}