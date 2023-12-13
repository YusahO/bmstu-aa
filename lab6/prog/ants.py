#!./venv/bin/python3

import random
import networkx as nx
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

def load_city_graph(file_name):
    return pd.read_csv(file_name)

def visualize_graph(city_df: pd.DataFrame):
    G = nx.from_pandas_edgelist(city_df, 'Destination', 'Order', edge_attr='Distance', create_using=nx.DiGraph())
    pos = nx.kamada_kawai_layout(G, scale=2)
    nx.draw(G, pos, with_labels=True, node_size=1500, node_color='lightblue', font_weight='bold', arrowsize=20)
    labels = nx.get_edge_attributes(G,'Distance')
    nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
    plt.show()

def dataframe_to_city_graph(df: pd.DataFrame):
    city_graph = {}
    for _, row in df.iterrows():
        origin_city = row['Order']
        destination_city = row['Destination']
        distance = row['Distance']
        if origin_city not in city_graph:
            city_graph[origin_city] = {}
        if destination_city not in city_graph:
            city_graph[destination_city] = {}
        city_graph[origin_city][destination_city] = distance
        city_graph[destination_city][origin_city] = distance
    return city_graph


def initialize_pheromones(city_graph, initial_pheromone):
    pheromones = {(city1, city2): initial_pheromone for city1 in city_graph for city2 in city_graph[city1]}
    return pheromones

def move_ant(current_city, route, city_graph, pheromones):
    available_cities = [city for city in city_graph[current_city] if city not in route]
    if not available_cities:  
        return route, 0
    probabilities = []
    total_pheromones = sum(pheromones[(current_city, city)] for city in available_cities)
    if total_pheromones == 0:  
        chosen_city = random.choice(available_cities)
    else:
        for city in available_cities:
            probability = pheromones[(current_city, city)] / total_pheromones
            probabilities.append(probability)
        chosen_city = random.choices(available_cities, weights=probabilities)[0]
    route.append(chosen_city)
    return chosen_city, 1

def update_pheromones(pheromones, routes, city_graph, evaporation_factor, elite_ants):
    elite_routes = sorted(routes, key=lambda x: sum(city_graph[x[i]][x[i + 1]] for i in range(len(x) - 1)))[:elite_ants]
    for route in elite_routes:
        route_length = sum(city_graph[route[i]][route[i + 1]] for i in range(len(route) - 1))
        for i in range(len(route) - 1):
            pheromones[(route[i], route[i + 1])] += 2 / route_length

    for edge in pheromones:
        pheromones[edge] *= (1 - evaporation_factor)
        for route in routes:
            route_length = sum(city_graph[route[i]][route[i + 1]] for i in range(len(route) - 1))
            for i in range(len(route) - 1):
                pheromones[(route[i], route[i + 1])] += 1 / route_length
    return pheromones

def aco_with_elite_ants(city_graph, n_iterations, n_ants, evaporation_factor, elite_ants):
    pheromones = initialize_pheromones(city_graph, 1.0)
    best_route = None
    best_route_length = float('inf')
    
    for _ in range(n_iterations):
        routes = []
        for _ in range(n_ants):
            current_city = random.choice(list(city_graph.keys()))
            route = [current_city]
            while len(route) < len(city_graph):
                current_city, moved = move_ant(current_city, route, city_graph, pheromones)
                if not moved:
                    break
            routes.append(route)

        pheromones = update_pheromones(pheromones, routes, city_graph, evaporation_factor, elite_ants)

        for route in routes:
            route_length = sum(city_graph[route[i]][route[i + 1]] for i in range(len(route) - 1))
            if route_length < best_route_length:
                best_route_length = route_length
                best_route = route

    return best_route

def main():
    file_name = 'prog/cities.csv'
    city_df = load_city_graph(file_name)
    city_graph = dataframe_to_city_graph(city_df)
    n_iterations = 10000
    n_ants = 5
    evaporation_factor = 0.5
    elite_ants = 2
    optimal_route = aco_with_elite_ants(city_graph, n_iterations, n_ants, evaporation_factor, elite_ants)
    print(optimal_route)

if __name__ == "__main__":
    main()