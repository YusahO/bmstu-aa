#include "pipeline.h"
#include "measure.h"

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
            int req_cnt = utils::get_request_count();
            auto datasets = utils::pick_datasets(req_cnt);
            std::tuple cls_params = utils::get_clust_params();
            consequent(req_cnt, datasets, cls_params);
        }
        else if (choice == 2)
        {
            int req_cnt = utils::get_request_count();
            auto datasets = utils::pick_datasets(req_cnt);
            std::tuple cls_params = utils::get_clust_params();
            concurrent(req_cnt, datasets, cls_params);
        }
        else if (choice == 3)
        {
            TimeMeasureFiles(5);
            TimeMeasureRequests(5, 50, 5, 10);
        }
    }
    return 0;
}