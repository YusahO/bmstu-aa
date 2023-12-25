static void service_01(
    int req_cnt,
    const std::vector<std::string> &datasets,
    ts_queue<stages_t *> &q1)
{
    for (int i = 0; i < req_cnt; ++i)
    {
        stages_t *s = new stages_t();
        clock_gettime(CLOCK_REALTIME, &s->parsed.op_start);
        s->parsed.notes = read_dataset(datasets[i]);
        clock_gettime(CLOCK_REALTIME, &s->parsed.op_end);
        q1.push(s);
    }
}

static void service_02(
    int req_cnt,
    ts_queue<stages_t *> &q1,
    ts_queue<stages_t *> &q2)
{
    for (int i = 0; i < req_cnt; ++i)
    {
        stages_t *s = q1.pop();

        clock_gettime(CLOCK_REALTIME, &s->embedded.op_start);
        s->embedded.embeddings = extract_bigrams(s->parsed.notes);
        clock_gettime(CLOCK_REALTIME, &s->embedded.op_end);
        q2.push(s);
    }
}

static void service_03(
    int req_cnt,
    std::tuple<int, double, double, int> cls_params,
    ts_queue<stages_t *> &q2,
    std::vector<std::unique_ptr<stages_t>> &pool,
    bool verbose)
{
    for (int i = 0; i < req_cnt; ++i)
    {
        stages_t *s = q2.pop();
        auto [k, m, conv_threshold, max_iters] = cls_params;

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
}

void concurrent(
    int req_cnt,
    const std::vector<std::string> &datasets,
    std::tuple<int, double, double, int> cls_params,
    bool verbose)
{
    std::vector<std::unique_ptr<stages_t>> pool;
    ts_queue<stages_t *> q1;
    ts_queue<stages_t *> q2;

    std::thread t_01(service_01, req_cnt, std::cref(datasets), std::ref(q1));
    std::thread t_02(service_02, req_cnt, std::ref(q1), std::ref(q2));
    std::thread t_03(service_03, req_cnt, cls_params, std::ref(q2), std::ref(pool), verbose);

    t_01.join();
    t_02.join();
    t_03.join();

    if (verbose)
        dump_pool(pool, "conc.txt");
}
