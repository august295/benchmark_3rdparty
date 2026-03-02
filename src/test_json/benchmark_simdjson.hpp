#pragma once

#include <benchmark/benchmark.h>

#include <simdjson.h>

#include "benchmark_common_json.hpp"

static void BM_Simdjson_Parse_File(benchmark::State& state, const std::string& filename)
{
    auto        fsize   = get_file_size(filename);
    std::string content = read_file_to_string(filename);

    for (auto _ : state)
    {
        simdjson::dom::parser  parser;
        simdjson::dom::element j = parser.parse(content);
        benchmark::DoNotOptimize(j);
    }

    state.SetBytesProcessed(state.iterations() * fsize);
}
BENCHMARK_CAPTURE(BM_Simdjson_Parse_File, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(BM_Simdjson_Parse_File, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(BM_Simdjson_Parse_File, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(BM_Simdjson_Parse_File, 1MB, "json/1MB.json");

static void BM_Simdjson_Parse_String(benchmark::State& state, const std::string& filename)
{
    std::string content = read_file_to_string(filename);
    auto        size    = content.size();

    for (auto _ : state)
    {
        simdjson::dom::parser  parser;
        simdjson::dom::element j = parser.parse(content);
        benchmark::DoNotOptimize(j);
    }

    state.SetBytesProcessed(state.iterations() * size);
}
BENCHMARK_CAPTURE(BM_Simdjson_Parse_String, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(BM_Simdjson_Parse_String, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(BM_Simdjson_Parse_String, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(BM_Simdjson_Parse_String, 1MB, "json/1MB.json");
