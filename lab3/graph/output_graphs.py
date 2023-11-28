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

def output(x, *y, output_file='', scale='linear'):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, np.divide(y[0], 1000), color='r', marker='o', linestyle=':', label='Блинная сортировка')
    splt.plot(x, np.divide(y[1], 1000), color='b', marker='^', label='Гномья сортировка')
    splt.plot(x, np.divide(y[2], 1000), color='orange', marker='s', linestyle='-.', label='Быстрая сортировка')
    splt.set_yscale(scale)
    splt.grid(True)
    plt.xlabel('Размер (элем.)')
    plt.ylabel('Время (мкс)')
    splt.legend()
    plt.savefig(output_file)


def main():
    data = parse_table('graph/table_forward.txt')
    iter_indices = list(int(iter[0]) for iter in data)
    pancake = list(float(iter[1]) for iter in data)
    gnome = list(float(iter[2]) for iter in data)
    quick = list(float(iter[3]) for iter in data)
    output(iter_indices, pancake, gnome, quick, output_file='report/images/time/forward.svg', scale='log')

    data = parse_table('graph/table_random.txt')
    iter_indices = list(int(iter[0]) for iter in data)
    pancake = list(float(iter[1]) for iter in data)
    gnome = list(float(iter[2]) for iter in data)
    quick = list(float(iter[3]) for iter in data)
    output(iter_indices, pancake, gnome, quick, output_file='report/images/time/random.svg')

    data = parse_table('graph/table_backward.txt')
    iter_indices = list(int(iter[0]) for iter in data)
    pancake = list(float(iter[1]) for iter in data)
    gnome = list(float(iter[2]) for iter in data)
    quick = list(float(iter[3]) for iter in data)
    output(iter_indices, pancake, gnome, quick, output_file='report/images/time/backward.svg')

    return 0

if __name__ == "__main__":
    main()
