#include <sstream>
#include <string>

#include <benchmark/benchmark.h>
#include <rapidcsv.h>

#include "benchmark_common.hpp"

static void BM_RapidCSV_Parse_Args(benchmark::State& state)
{
    auto rows = state.range(0);
    auto csv  = generate_csv(rows, 5);

    for (auto _ : state)
    {
        std::stringstream  ss(csv);
        rapidcsv::Document doc(ss, rapidcsv::LabelParams(0, 0));
        benchmark::DoNotOptimize(doc);
    }
}
BENCHMARK(BM_RapidCSV_Parse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});

static void BM_RapidCSV_Traverse_Args(benchmark::State& state)
{
    auto rows = state.range(0);
    auto csv  = generate_csv(rows, 5);

    for (auto _ : state)
    {
        std::stringstream  ss(csv);
        rapidcsv::Document doc(ss, rapidcsv::LabelParams(0, 0));
        long long          sum = 0;
        for (int i = 0; i < doc.GetRowCount(); ++i)
        {
            for (int j = 0; j < doc.GetColumnCount(); ++j)
            {
                sum += doc.GetCell<long long>(j, i);
            }
        }
        benchmark::DoNotOptimize(sum);
    }
}
BENCHMARK(BM_RapidCSV_Traverse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});
