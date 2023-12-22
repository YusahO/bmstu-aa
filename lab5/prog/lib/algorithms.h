#pragma once

#include <vector>
#include <string>

#include "pipe_request.h"

std::vector<note_vector_t> read_dataset(const std::string &descr_files);
std::vector<point_vec_t> extract_bigrams(const std::vector<note_vector_t> &notes);
std::tuple<membership_t, point_vec_t> init_structures(int d, int k);
void c_means(
    membership_t &membership, point_vec_t &cluster_centers,
    const point_vec_t &data,
    double m, double conv_threshold, int max_iters);