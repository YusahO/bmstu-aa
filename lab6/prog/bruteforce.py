import numpy as np
import itertools as it

# def calculate_path_length(path, distances):
#     length = 0
#     for i in range(len(path) - 1):
#         length += distances[path[i]][path[i+1]]
#     length += distances[path[-1]][path[0]]  # Добавляем расстояние обратно к начальной точке
#     return length

# def brute_force(distances, n):
#     shortest_path = None
#     shortest_length = float('inf')

#     for path in it.permutations(range(n)):
#         length = calculate_path_length(path, distances)
#         if length < shortest_length:
#             shortest_length = length
#             shortest_path = path

#     return shortest_length, shortest_path


def brute_force(matrix, size):
    places = np.arange(size)
    places_combs = list()

    for combination in it.permutations(places):
        combs = list(combination)
        places_combs.append(combs)

    best_dist = float("inf")

    for i in range(len(places_combs)):
        # places_combs[i].append(places_combs[i][0])
        cur_dist = 0
        for j in range(size - 1):
            start = places_combs[i][j]
            end = places_combs[i][j + 1]
            cur_dist += matrix[start][end]

        if (cur_dist < best_dist):
            best_dist = cur_dist
            best_path = places_combs[i][1:]
    
    return best_dist, best_path