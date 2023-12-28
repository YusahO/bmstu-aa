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
