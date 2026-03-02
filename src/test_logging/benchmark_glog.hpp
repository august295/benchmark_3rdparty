#pragma once

#include "benchmark_common_log.hpp"

#include <glog/logging.h>

static void BM_Glog_St(benchmark::State& state)
{
    auto count = state.range(0);
    for (auto _ : state)
    {
        for (size_t i = 0; i < count; i++)
        {
            LOG(INFO) << "info message " << i;
        }
    }
    state.counters["ops/sec"] = benchmark::Counter(state.iterations() * count, benchmark::Counter::kIsRate);
}

static void BM_Glog_Mt(benchmark::State& state)
{
    auto count = state.range(0);
    for (auto _ : state)
    {
        for (size_t i = 0; i < count; i++)
        {
            LOG(INFO) << "info message " << i;
        }
    }
    state.counters["ops/sec"] = benchmark::Counter(state.iterations() * count, benchmark::Counter::kIsRate);
}

static void custom_args_glog(benchmark::internal::Benchmark* b)
{
    for (int i = 10; i <= 10000; i = i * 10)
    {
        b->Arg(i);
    }
}

static void setup_glog()
{
    google::InitGoogleLogging("glog_bench");
    google::SetLogDestination(google::GLOG_INFO, "logs/glog_bench.log");
    google::SetStderrLogging(google::GLOG_WARNING);
}

BENCHMARK(BM_Glog_St)->Apply(custom_args_glog);
BENCHMARK(BM_Glog_Mt)->Apply(custom_args_glog)->ThreadRange(1, 16);
