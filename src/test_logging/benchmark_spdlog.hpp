#pragma once

#include "benchmark_common_log.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

static void BM_Spdlog_St(benchmark::State& state)
{
    auto count  = state.range(0);
    auto logger = spdlog::get("spdlog_st");
    for (auto _ : state)
    {
        for (size_t i = 0; i < count; i++)
        {
            logger->info("info message {}", i);
        }
    }
    state.counters["ops/sec"] = benchmark::Counter(state.iterations() * count, benchmark::Counter::kIsRate);
}

static void BM_Spdlog_Mt(benchmark::State& state)
{
    auto count  = state.range(0);
    auto logger = spdlog::get("spdlog_mt");
    for (auto _ : state)
    {
        for (size_t i = 0; i < count; i++)
        {
            logger->info("info message {}", i);
        }
    }
    state.counters["ops/sec"] = benchmark::Counter(state.iterations() * count, benchmark::Counter::kIsRate);
}

static void custom_args_spdlog(benchmark::internal::Benchmark* b)
{
    for (int i = 10; i <= 10000; i = i * 10)
    {
        b->Arg(i);
    }
}

static void setup_spdlog()
{
    auto logger_st = spdlog::basic_logger_st("spdlog_st", "logs/spdlog_st.log");
    spdlog::set_default_logger(logger_st);

    auto logger_mt = spdlog::basic_logger_mt("spdlog_mt", "logs/spdlog_mt.log");
    spdlog::set_default_logger(logger_mt);
}

BENCHMARK(BM_Spdlog_St)->Apply(custom_args_spdlog);
BENCHMARK(BM_Spdlog_Mt)->Apply(custom_args_spdlog)->ThreadRange(1, 16);
