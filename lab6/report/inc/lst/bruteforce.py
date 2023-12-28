def brute_force(matrix, size):
    places = np.arange(size)
    places_combs = list()

    for combination in it.permutations(places):
        combs = list(combination)
        places_combs.append(combs)

    best_dist = float("inf")

    for i in range(len(places_combs)):
        cur_dist = 0
        for j in range(size - 1):
            start = places_combs[i][j]
            end = places_combs[i][j + 1]
            cur_dist += matrix[start][end]

        if (cur_dist < best_dist):
            best_dist = cur_dist
            best_path = places_combs[i]

    return best_dist, best_path
