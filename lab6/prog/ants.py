import random
import numpy as np

# num_nodes = 5
# pheromones = np.ones((num_nodes, num_nodes))
# visibilities = np.array([
#     [0, 2, 3, 4, 5],
#     [1, 0, 2, 3, 4],
#     [2, 1, 0, 2, 3],
#     [3, 2, 1, 0, 2],
#     [0, 3, 2, 1, 0]
# ])


def generate_ant_paths(num_ants, num_nodes):
    ant_paths = []
    for _ in range(num_ants):
        path = [0]
        unvisited_nodes = list(range(1, num_nodes))
        random.shuffle(unvisited_nodes)
        path.extend(unvisited_nodes)
        path.append(0)
        ant_paths.append(path)
    return ant_paths


def update_pheromones(num_ants, pheromones, ant_paths, evaporation_rate):
    for i in range(num_ants):
        path = ant_paths[i]
        for j in range(len(pheromones)):
            start, end = path[j], path[j + 1]
            pheromones[start, end] *= (1 - evaporation_rate)
            pheromones[start, end] += 1 / len(path)


def calculate_path_cost(path, alpha, beta, visibility, pheromones):
    cost = 0
    for i in range(len(path) - 1):
        start, end = path[i], path[i + 1]
        pheromone_level = pheromones[start][end]
        edge_visibility = visibility[start][end]
        cost += (pheromone_level ** alpha) * (edge_visibility ** beta)
    return cost


def select_elite_ants(ant_paths, alpha, beta, visibility, pheromones, num_elite_ants):
    elite_ant_paths = sorted(ant_paths, key=lambda path: calculate_path_cost(path, alpha, beta, visibility, pheromones))[
        :num_elite_ants]
    return elite_ant_paths


def ant_algorithm(visibility,
                  evaporation_rate=0.5,
                  alpha=1,
                  beta=2,
                  num_ants=10,
                  num_iterations=100,
                  num_elite_ants=2):
    num_nodes = len(visibility)
    pheromones = np.ones((num_nodes, num_nodes))
    best_path = None
    best_cost = float('inf')
    for _ in range(num_iterations):
        ant_paths = generate_ant_paths(num_ants, num_nodes)
        elite_ant_paths = select_elite_ants(ant_paths, alpha, beta, visibility, pheromones, num_elite_ants)

        for path in elite_ant_paths:
            cost = calculate_path_cost(path, alpha, beta, visibility, pheromones)
            if cost < best_cost:
                best_path = path
                best_cost = cost
        for path in ant_paths:
            if path[0] == 0 and path[-1] == 0:
                cost = sum(visibility[path[i]][path[i+1]]
                           for i in range(num_nodes-1))
                if cost < best_cost:
                    best_path = path[:-1]
                    best_cost = cost
        update_pheromones(num_ants, pheromones, ant_paths, evaporation_rate)

    return best_cost, best_path
