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

def output_odd(x, *y):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, y[0], color='r', marker='o', linestyle=':', label='Классический алгоритм')
    splt.plot(x, y[1], color='g', marker='*', label='Алгоритм Винограда')
    splt.plot(x, y[2], color='b', marker='s', linestyle='-.', label='Алгоритм Винограда (оптимизир.)')
    splt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (нс)')
    splt.legend()
    plt.savefig('report/images/time/all_odd.svg')

def output_even(x, *y):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, y[0], color='r', marker='o', linestyle=':', label='Классический алгоритм')
    splt.plot(x, y[1], color='g', marker='*', label='Алгоритм Винограда')
    splt.plot(x, y[2], color='b', marker='s', linestyle='-.', label='Алгоритм Винограда (оптимизир.)')
    splt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (нс)')
    splt.legend()
    plt.savefig('report/images/time/all_even.svg')

def output_strassen(x, *y):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, np.divide(y[0], 1000), color='r', marker='o', linestyle=':', label='Классический алгоритм')
    splt.plot(x, np.divide(y[1], 1000), color='b', marker='^', label='Алгоритм Винограда')
    splt.plot(x, np.divide(y[2], 1000), color='orange', marker='s', linestyle='-.', label='Алгоритм Винограда (оптимизир.)')
    splt.plot(x, np.divide(y[3], 1000), color='g', marker='>', linestyle='--', label='Алгоритм Штрассена')
    splt.set_yscale('log')
    splt.grid(True)
    plt.xlabel('Длина (симв.)')
    plt.ylabel('Время (мкс)')
    splt.legend()
    plt.savefig('report/images/time/strassen.svg')


def main():
    data = parse_table('graph/table_1.txt')
    iter_indices = list(int(iter[0]) for iter in data)
    classic_odd = list(float(iter[1]) for iter in data)
    winograd_odd = list(float(iter[2]) for iter in data)
    winograd_odd_opt = list(float(iter[3]) for iter in data)

    output_odd(iter_indices, classic_odd, winograd_odd, winograd_odd_opt)

    data = parse_table('graph/table_0.txt')
    iter_indices = list(int(iter[0]) for iter in data)
    classic_even = list(float(iter[1]) for iter in data)
    winograd_even = list(float(iter[2]) for iter in data)
    winograd_even_opt = list(float(iter[3]) for iter in data)

    output_even(iter_indices, classic_even, winograd_even, winograd_even_opt)

    data = parse_table('graph/table_2.txt')
    iter_indices = list(int(iter[0]) for iter in data)
    classic = list(float(iter[1]) for iter in data)
    winograd = list(float(iter[2]) for iter in data)
    winograd_opt = list(float(iter[3]) for iter in data)
    strassen = list(float(iter[4]) for iter in data)

    output_strassen(iter_indices, classic, winograd, winograd_opt, strassen)

    return 0

if __name__ == "__main__":
    main()
