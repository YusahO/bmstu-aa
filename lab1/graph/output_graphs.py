#!./graph/venv/bin/python3

import re
import matplotlib.pyplot as plt
import numpy as np

def parse_table(path):
    with open(path, 'r') as tf:
        data = []
        for l in tf:
            numbers = re.findall(r'\b\d+\.?\d*\b', l)
            if len(numbers) != 0:
                data.append(numbers) 
    return data

def output_nonrec(x, *y):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, np.divide(y[0], 1000), color='r', marker='o', linestyle=':', label='Нерекурсивный алгоритм Левенштейна')
    splt.plot(x, np.divide(y[1], 1000), color='b', marker='*', label='Нерекурсивный алгоритм Дамерау-Левенштейна')
    splt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (мкс)')
    splt.legend()
    plt.savefig('report/images/nonrec.svg')

def output_rec(x, *y):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, y[0], color='r', marker='o', linestyle=':', label='Рекурсивный алгоритм Дамерау-Левенштейна')
    splt.plot(x, y[1], color='b', marker='*', label='Рекурсивный алгоритм Дамерау-Левенштейна с использованием кэша')
    splt.set_yscale('log')
    splt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (нс)')
    splt.legend()
    plt.savefig('report/images/rec.svg')

def output_fastest(x, *y):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, y[0], color='r', marker='o', linestyle=':', label='Нерекурсивный алгоритм Дамерау-Левенштейна')
    splt.plot(x, y[1], color='g', marker='*', label='Рекурсивный алгоритм Дамерау-Левенштейна')
    splt.plot(x, y[2], color='b', marker='s', linestyle='-.', label='Рекурсивный алгоритм Дамерау-Левенштейна с использованием кэша')
    splt.set_yscale('log')
    splt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (нс)')
    splt.legend()
    plt.savefig('report/images/dl_all.svg')


def main():
    data = parse_table('graph/table.txt')

    iter_indices = list(int(iter[0]) for iter in data)
    lev_iter = list(float(iter[1]) for iter in data)
    damlev_iter = list(float(iter[2]) for iter in data)
    damlev_rec = list(float(data[i][3]) for i, _ in enumerate(data) if i < 10)
    damlev_rec_cached = list(float(data[i][4]) for i, _ in enumerate(data) if i < 10)

    output_nonrec(iter_indices, lev_iter, damlev_iter)
    output_rec(iter_indices[:10], damlev_rec, damlev_rec_cached[:10])
    output_fastest(iter_indices[:10], damlev_iter[:10], damlev_rec[:10], damlev_rec_cached[:10])

    return 0

if __name__ == "__main__":
    main()
