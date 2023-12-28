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

