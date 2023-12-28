import numpy as np
from random import random
from defines import MIN_PHEROMONE

def make_summer(matrix):
    mat = np.copy(matrix)
    mat[3][2] /= 2 
    mat[2][3] *= 4
    mat[0][5] /= 2
    mat[5][0] *= 4
    mat[3][6] /= 2
    mat[6][3] *= 4
    return mat

def make_winter(matrix):
    mat = np.copy(matrix)
    mat[3][4] *= 10
    mat[4][3] *= 10
    mat[1][5] *= 10
    mat[5][1] *= 10
    mat[2][9] *= 10
    mat[9][2] *= 10
    mat[8][4] *= 10
    mat[4][8] *= 10
    return mat

def calc_q(matrix, size):
    q = 0
    count = 0
    for i in range(size):
        for j in range(size):
            if i != j:
                q += matrix[i][j]
                count += 1
    return q / count


def calc_pheromones(size):
    min_phero = 1
    pheromones = [[min_phero for _ in range(size)] for _ in range(size)]
    return np.array(pheromones, dtype=np.float128)


def calc_visibility(matrix, size):
    visibility = [
        [(1.0 / matrix[i][j] if (i != j and matrix[i][j] != 0) else 0) for j in range(size)]
        for i in range(size)
    ]
    return visibility


def calc_visited_places(route, ants):
    visited = [list() for _ in range(ants)]
    for ant in range(ants):
        visited[ant].append(route[ant])
    return visited


def calc_length(matrix, route):
    length = 0
    for way_len in range(1, len(route)):
        length += matrix[route[way_len - 1], route[way_len]]
    return length


def find_paths(pheromones, visibility, visited, places, ant, alpha, beta):
    pk = [0] * places
    for place in range(places):
        if place not in visited[ant]:
            ant_place = visited[ant][-1]
            pk[place] = pow(pheromones[ant_place][place], alpha) * pow(
                visibility[ant_place][place], beta
            )
        else:
            pk[place] = 0
    sum_pk = sum(pk)
    for place in range(places):
        pk[place] /= sum_pk
    return pk


def update_pheromones_with_elite(
    matrix,
    places,
    visited,
    pheromones,
    q,
    k_evaporation,
    elite_ant_paths,
    elite_pheromone_deposit,
):
    ants = places
    for i in range(places):
        for j in range(places):
            delta = 0
            for ant in range(ants):
                length = calc_length(matrix, visited[ant])
                delta += q / length
            for elite_path in elite_ant_paths:
                if (i, j) in zip(elite_path, elite_path[1:]):
                    delta += elite_pheromone_deposit
            pheromones[i][j] *= 1 - k_evaporation
            pheromones[i][j] += delta
            if pheromones[i][j] < MIN_PHEROMONE:
                pheromones[i][j] = MIN_PHEROMONE
    return pheromones


def choose_next_loc_by_possibility(pk):
    posibility = random()
    choice = 0
    chosen_loc = 0
    while (choice < posibility) and (chosen_loc < len(pk)):
        choice += pk[chosen_loc]
        chosen_loc += 1
    return chosen_loc


def ant_algorithm(matrix, size, alpha, beta, k_evaporation, days, elite_ants, elite_pheromone_deposit=1.0):
    q = calc_q(matrix, size)
    best_path = []
    best_dist = float("inf")
    pheromones = calc_pheromones(size)
    ants = size

    elite_ant_paths = []

    matrices = [make_summer(matrix), make_winter(matrix)]
    season = 0

    visibilities = [
        calc_visibility(matrices[0], size),
        calc_visibility(matrices[1], size),
    ]

    for day in range(days):
        if day % 60 == 0:
            season = 1 - season
        
        route = np.arange(size)
        visited = calc_visited_places(route, ants)

        for ant in range(ants):
            while len(visited[ant]) != size:
                pk = find_paths(
                    pheromones, visibilities[season], visited, size, ant, alpha, beta
                )
                chosen_loc = choose_next_loc_by_possibility(pk)
                visited[ant].append(chosen_loc - 1)
                if ant < elite_ants:
                    elite_ant_paths.append(visited[ant])
                    
            cur_length = calc_length(matrix, visited[ant])
            if cur_length < best_dist:
                best_dist = cur_length
                best_path = visited[ant]

        for elite_path in elite_ant_paths:
            for i in range(len(elite_path) - 1):
                pheromones[elite_path[i]][elite_path[i + 1]] *= (
                    1 + elite_pheromone_deposit
                )

        pheromones = update_pheromones_with_elite(
            matrices[season],
            size,
            visited,
            pheromones,
            q,
            k_evaporation,
            elite_ant_paths,
            elite_pheromone_deposit,
        )
        pheromones /= np.linalg.norm(pheromones)

    return best_dist, best_path
