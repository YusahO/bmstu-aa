#include "pipeline.h"
#include <fstream>
#include <algorithm>

struct pool_result_t
{
public:
    pool_result_t() = default;
    bool operator<(const pool_result_t &other) const
    {
        return this->nanosec < other.nanosec;
    }

    pool_result_t &operator=(const pool_result_t &other)
    {
        this->message = other.message;
        this->nanosec = other.nanosec;
        return *this;
    }

    long long nanosec;
    std::string message;
};

static void dump_pool(std::vector<std::unique_ptr<stages_t>> &pool, const std::string &filename)
{
    std::vector<pool_result_t> pool_sort(pool.size() * 6);
    timespec min = pool[0]->parsed.op_start;
    for (size_t i = 0; i < pool.size(); ++i)
    {
        if (min.tv_sec > pool[i]->parsed.op_start.tv_sec || (min.tv_sec == pool[i]->parsed.op_start.tv_sec && min.tv_nsec > pool[i]->parsed.op_start.tv_nsec))
            min = pool[i]->parsed.op_start;
    }

    long long min_nano = min.tv_sec * 1000000000 + min.tv_nsec;
    for (size_t i = 0; i < pool.size(); ++i)
    {
        long long nanosec = pool[i]->parsed.op_start.tv_sec * 1000000000 + pool[i]->parsed.op_start.tv_nsec;
        nanosec -= min_nano;
        char *buf = new char[50];
        snprintf(buf, 50, "Request %lu start PARSING: %lld ns", i, nanosec);
        pool_sort[i * 6].message = std::string(buf);
        pool_sort[i * 6].nanosec = nanosec;

        nanosec = pool[i]->parsed.op_end.tv_sec * 1000000000 + pool[i]->parsed.op_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end PARSING: %lld ns", i, nanosec);
        pool_sort[i * 6 + 1].message = std::string(buf);
        pool_sort[i * 6 + 1].nanosec = nanosec;

        nanosec = pool[i]->embedded.op_start.tv_sec * 1000000000 + pool[i]->embedded.op_start.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu start EMBEDDING: %lld ns", i, nanosec);
        pool_sort[i * 6 + 2].message = std::string(buf);
        pool_sort[i * 6 + 2].nanosec = nanosec;

        nanosec = pool[i]->embedded.op_end.tv_sec * 1000000000 + pool[i]->embedded.op_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end EMBEDDING: %lld ns", i, nanosec);
        pool_sort[i * 6 + 3].message = std::string(buf);
        pool_sort[i * 6 + 3].nanosec = nanosec;

        nanosec = pool[i]->clusterized.op_start.tv_sec * 1000000000 + pool[i]->clusterized.op_start.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu start CLUSTERING: %lld ns", i, nanosec);
        pool_sort[i * 6 + 4].message = std::string(buf);
        pool_sort[i * 6 + 4].nanosec = nanosec;

        nanosec = pool[i]->clusterized.op_end.tv_sec * 1000000000 + pool[i]->clusterized.op_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end CLUSTERING: %lld ns", i, nanosec);
        pool_sort[i * 6 + 5].message = std::string(buf);
        pool_sort[i * 6 + 5].nanosec = nanosec;
    }
    std::sort(pool_sort.begin(), pool_sort.end());
    std::ofstream fout;
    fout.open(filename, std::ios_base::app);
    for (auto &entry : pool_sort)
    {
        fout << entry.message << "\n";
    }
    fout.close();
}

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
    std::vector<std::unique_ptr<stages_t>> &pool)
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

void concurrent()
{
    int req_cnt = utils::get_request_count();
    auto datasets = utils::pick_datasets(req_cnt);
    std::tuple cls_params = utils::get_clust_params();

    std::vector<std::unique_ptr<stages_t>> pool;
    ts_queue<stages_t *> q1;
    ts_queue<stages_t *> q2;

    std::thread t_01(service_01, req_cnt, std::cref(datasets), std::ref(q1));
    std::thread t_02(service_02, req_cnt, std::ref(q1), std::ref(q2));
    std::thread t_03(service_03, req_cnt, cls_params, std::ref(q2), std::ref(pool));

    t_01.join();
    t_02.join();
    t_03.join();

    dump_pool(pool, "conc.txt");
}