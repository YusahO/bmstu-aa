def calc_pheromones(size):
    min_phero = 1
    pheromones = [[min_phero for _ in range(size)] for _ in range(size)]
    return np.array(pheromones, dtype=np.float128)
