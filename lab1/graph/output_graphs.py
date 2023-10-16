import re
import matplotlib.pyplot as plt

def parse_table(path):
    with open(path, 'r') as tf:
        data = []
        for l in tf:
            numbers = re.findall(r'\b\d+\.?\d*\b', l)
            if len(numbers) != 0:
                data.append(numbers) 
    return data

def output_nonrec(x, *y):
    plt.plot(x, y[0], color='r', marker='o', linestyle=':', label='Нерекурсивный алгоритм Левенштейна')
    plt.plot(x, y[1], color='b', marker='*', label='Нерекурсивный алгоритм Дамерау-Левенштейна')
    plt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (нс)')
    plt.legend()
    plt.show()


def main():
    data = parse_table('graph/table.txt')

    iter_indices = list(int(iter[0]) for iter in data)
    lev_iter = list(float(iter[1]) for iter in data)
    damlev_iter = list(float(iter[2]) for iter in data)
    damlev_rec = list(float(data[i][3]) for i, _ in enumerate(data) if i < 10)
    damlev_rec_cached = list(float(data[i][4]) for i, _ in enumerate(data) if i < 10)

    output_nonrec(iter_indices, lev_iter, damlev_iter)

    return 0

if __name__ == "__main__":
    main()
