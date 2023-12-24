#!./graph/venv/bin/python3

import re
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def parse_table(path):
    with open(path, 'r') as tf:
        data = []
        for l in tf:
            numbers = re.findall(r'\b\d+\.?\d*\b', l)
            if len(numbers) != 0:
                data.append(numbers)

    df = pd.DataFrame(data)
    print(df.to_csv(index=False))
    return data

def output_queries(x, *y, output_file='', scale='linear'):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, np.divide(y[0], 1000), color='r', marker='o', linestyle=':', label='Линейная')
    splt.plot(x, np.divide(y[1], 1000), color='b', marker='^', label='Конвейерная')
    splt.set_yscale(scale)
    splt.grid(True)
    plt.xlabel('К-во заявок (шт.)')
    plt.ylabel('Время (мс)')
    splt.legend()
    plt.savefig(output_file)

def output_files(x, *y, output_file='', scale='linear'):
    fig = plt.figure(figsize=(10, 7))
    splt = fig.add_subplot()
    splt.plot(x, np.divide(y[0], 1000), color='r', marker='o', linestyle=':', label='Линейная')
    splt.plot(x, np.divide(y[1], 1000), color='b', marker='^', label='Конвейерная')
    splt.set_yscale(scale)
    splt.grid(True)
    plt.xlabel('К-во файлов (шт.)')
    plt.ylabel('Время (мс)')
    splt.legend()
    plt.savefig(output_file)


def main():
    data = parse_table('graph/table.txt')
    iter_indices = list(float(iter[0]) for iter in data)
    cons = list(float(iter[1]) for iter in data)
    para = list(float(iter[2]) for iter in data)
    output_queries(iter_indices, cons, para, scale='log', output_file='report/inc/img/time_queries.pdf')

    data = parse_table('graph/table_files.txt')
    iter_indices = list(float(iter[0]) for iter in data)
    cons = list(float(iter[1]) for iter in data)
    para = list(float(iter[2]) for iter in data)
    output_files(iter_indices, cons, para, scale='log', output_file='report/inc/img/time_files.pdf')

    return 0

if __name__ == "__main__":
    main()
