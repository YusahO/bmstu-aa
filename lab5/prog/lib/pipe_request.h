#pragma once

#include <vector>
#include <ctime>
#include <memory>

struct pipe_request
{
    virtual ~pipe_request() = default;

    timespec op_start, op_end;
};

using note_t = unsigned char;
using point_vec_t = std::vector<std::vector<double>>;
using membership_t = std::vector<std::vector<double>>;
using note_vector_t = std::vector<note_t>;
using bigram_vector_t = std::vector<std::vector<note_t>>;

struct parsed_dataset_request : pipe_request
{
    std::vector<note_vector_t> notes;
};

struct embedded_dataset_request : pipe_request
{
    std::vector<point_vec_t> embeddings;
};

struct clusterized_request : pipe_request
{
    std::vector<std::pair<membership_t, point_vec_t>> results;
};