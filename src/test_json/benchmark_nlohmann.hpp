#pragma once

#include <benchmark/benchmark.h>

#include <nlohmann/json.hpp>

#include "benchmark_common_json.hpp"

static void BM_Nlohmann_Parse_File(benchmark::State& state, const std::string& filename)
{
    auto fsize = get_file_size(filename);

    for (auto _ : state)
    {
        std::ifstream  f(filename);
        nlohmann::json j = nlohmann::json::parse(f);
        benchmark::DoNotOptimize(j);
    }

    state.SetBytesProcessed(state.iterations() * fsize);
}

BENCHMARK_CAPTURE(BM_Nlohmann_Parse_File, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_File, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_File, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_File, 1MB, "json/1MB.json");

static void BM_Nlohmann_Parse_String(benchmark::State& state, const std::string& filename)
{
    std::string content = read_file_to_string(filename);
    auto        size    = content.size();

    for (auto _ : state)
    {
        nlohmann::json j = nlohmann::json::parse(content);
        benchmark::DoNotOptimize(j);
    }

    state.SetBytesProcessed(state.iterations() * size);
}
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_String, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_String, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_String, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(BM_Nlohmann_Parse_String, 1MB, "json/1MB.json");

static void BM_Nlohmann_Write(benchmark::State& state)
{
    for (auto _ : state)
    {
        nlohmann::json j;
        j["pi"]                   = 3.141;
        j["happy"]                = true;
        j["name"]                 = "Niels";
        j["nothing"]              = nullptr;
        j["answer"]["everything"] = 42;
        j["list"]                 = {1, 0, 2};
        j["object"]               = {{"currency", "USD"}, {"value", 42.99}};

        std::string json_str = j.dump(4);
        benchmark::DoNotOptimize(json_str);
    }
}
BENCHMARK(BM_Nlohmann_Write);
