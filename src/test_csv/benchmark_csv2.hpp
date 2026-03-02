#include <string>

#include <benchmark/benchmark.h>
#include <csv2/csv2.hpp>

#include "benchmark_common.hpp"

static void BM_CSV2_Parse_Args(benchmark::State& state)
{
    auto rows = state.range(0);
    auto csv  = generate_csv(rows, 5);

    for (auto _ : state)
    {
        csv2::Reader<> reader;
        reader.parse(csv);
        benchmark::DoNotOptimize(reader);
    }
}
BENCHMARK(BM_CSV2_Parse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});

static void BM_CSV2_Traverse_Args(benchmark::State& state)
{
    auto rows = state.range(0);
    auto csv  = generate_csv(rows, 5);

    for (auto _ : state)
    {
        csv2::Reader<> reader;
        reader.parse(csv);
        long long sum = 0;
        for (const auto& row : reader)
        {
            for (const auto& cell : row)
            {
                std::string val;
                cell.read_value(val);
                sum += std::stoll(val);
            }
        }
        benchmark::DoNotOptimize(sum);
    }
}
BENCHMARK(BM_CSV2_Traverse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});
