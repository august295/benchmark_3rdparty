#include <benchmark/benchmark.h>
#include "benchmark_spdlog.hpp"
#include "benchmark_glog.hpp"

int main(int argc, char** argv)
{
    setup_spdlog();
    setup_glog();

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
}
