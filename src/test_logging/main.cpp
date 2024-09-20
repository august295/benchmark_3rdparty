#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include <benchmark/benchmark.h>

/**
 * @brief spdlog 测试
 */
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

static void bench_spdlog_mt_basic_file(benchmark::State& state)
{
    auto count  = state.range(0);
    auto name   = std::string("spdlog_basic_log_") + std::to_string(count);
    auto logger = spdlog::get(name);
    for (auto _ : state)
    {
        for (size_t i = 0; i < count; i++)
        {
            logger->trace("{} message", "trace");
            logger->debug("{} message", "debug");
            logger->info("{} message", "info");
            logger->warn("{} message", "warn");
            logger->error("{} message", "error");
            logger->critical("{} message", "critical");
        }
    }
}

static void custom_args_spdlog_mt_basic_file(benchmark::internal::Benchmark* b)
{
    for (int i = 10; i <= 10000; i = i * 10)
    {
        auto name     = std::string("spdlog_basic_log_") + std::to_string(i);
        auto filename = std::string("logs/spdlog_basic_log_") + std::to_string(i) + std::string(".txt");
        auto logger   = spdlog::basic_logger_mt(name, filename);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
        b->Arg(i);
    }
}

/**
 * @brief 日志测试
 *  1. 终端
 *  2. 文件
 */
BENCHMARK(bench_spdlog_mt_basic_file)->Apply(custom_args_spdlog_mt_basic_file)->Repetitions(1)->Iterations(10);
BENCHMARK_MAIN();