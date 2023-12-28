import os
import pandas as pd
import numpy as np
from ants import ant_algorithm
from bruteforce import brute_force

def get_coefficients():
    try:
        alpha = float(input("    Введите коэффициент alpha: " ))
        beta = 1 - alpha
        k_evaporation = float(input("    Введите коэффициент испарения: " ))
        days = int(input("    Введите кол-во дней: " ))
    except:
        print("    Введены недопустимые значения. Используются значения по умолчанию")
        alpha = 0
        beta = 1
        k_evaporation = 0.5
        days = 10
    return alpha, beta, k_evaporation, days

def run_algs(matrix: np.ndarray):
    mat_size = len(matrix)

    print("Алгоритм полного перебора")
    res = brute_force(matrix, mat_size)
    print("    Минимальная длина пути = ", res[0], "\n    Путь: ", res[1])

    print("Муравьиный алгоритм")
    # coefs = get_coefficients()
    res = ant_algorithm(matrix)
    print("    Минимальная длина пути = ", res[0], "\n    Путь: ", res[1])

def main():
    directory = '/home/daria/Документы/bmstu-AA/lab6/prog/data'
    all_files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    print('Доступные датасеты:')
    for n, f in enumerate(all_files, start=1):
        print(f'    {n}. {f}')
    run_algs(pd.read_csv('prog/data/cities.csv').values)

if __name__ == '__main__':
    main()