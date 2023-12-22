void consequent()
{
    int req_cnt = utils::get_request_count();
    auto datasets = utils::pick_datasets(req_cnt);
    auto [k, m, conv_threshold, max_iters] = utils::get_clust_params();

    std::vector<std::unique_ptr<stages_t>> pool;
    for (int i = 0; i < req_cnt; ++i)
    {
        stages_t *s = new stages_t;

        clock_gettime(CLOCK_REALTIME, &s->parsed.op_start);
        s->parsed.notes = read_dataset(datasets[i]);
        clock_gettime(CLOCK_REALTIME, &s->parsed.op_end);

        clock_gettime(CLOCK_REALTIME, &s->embedded.op_start);
        s->embedded.embeddings = extract_bigrams(s->parsed.notes);
        clock_gettime(CLOCK_REALTIME, &s->embedded.op_end);

        clock_gettime(CLOCK_REALTIME, &s->clusterized.op_start);
        for (const auto &embed : s->embedded.embeddings)
        {
            auto [mshp, cc] = init_structures(embed.size(), k);
            c_means(mshp, cc, embed, m, conv_threshold, max_iters);
            s->clusterized.results.emplace_back(std::move(mshp), std::move(cc));
        }
        clock_gettime(CLOCK_REALTIME, &s->clusterized.op_end);
        pool.emplace_back(s);
    }
    dump_pool(pool, "cons.txt");
}

