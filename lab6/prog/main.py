import pandas as pd
import numpy as np
from ants import antAlgorithm
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

    # print("Алгоритм полного перебора")
    # res = brute_force(matrix, mat_size)
    # print("    Минимальная длина пути = ", res[0], "\n    Путь: ", res[1])

    print("Муравьиный алгоритм")
    coefs = get_coefficients()
    res = antAlgorithm(matrix, mat_size, *coefs)
    print("    Минимальная длина пути = ", res[0], "\n    Путь: ", res[1])

# if __name__ == '__main__':
matrix = pd.read_csv('prog/cities.csv')
run_algs(matrix.values.astype(float))