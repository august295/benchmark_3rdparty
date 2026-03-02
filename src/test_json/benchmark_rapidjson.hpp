#pragma once

#include <benchmark/benchmark.h>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "benchmark_common_json.hpp"

static void BM_Rapidjson_Parse_File(benchmark::State& state, const std::string& filename)
{
    auto fsize = get_file_size(filename);

    for (auto _ : state)
    {
        std::ifstream             f(filename);
        rapidjson::IStreamWrapper isw(f);
        rapidjson::Document       d;
        d.ParseStream(isw);
        benchmark::DoNotOptimize(d);
    }

    state.SetBytesProcessed(state.iterations() * fsize);
}
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_File, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_File, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_File, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_File, 1MB, "json/1MB.json");

static void BM_Rapidjson_Parse_String(benchmark::State& state, const std::string& filename)
{
    std::string content = read_file_to_string(filename);
    auto        size    = content.size();

    for (auto _ : state)
    {
        rapidjson::Document d;
        d.Parse(content.c_str());
        benchmark::DoNotOptimize(d);
    }

    state.SetBytesProcessed(state.iterations() * size);
}
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_String, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_String, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_String, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(BM_Rapidjson_Parse_String, 1MB, "json/1MB.json");

static void BM_Rapidjson_Write(benchmark::State& state)
{
    for (auto _ : state)
    {
        rapidjson::Document d(rapidjson::Type::kObjectType);
        auto&               allocator = d.GetAllocator();

        d.AddMember("pi", 3.141, allocator);
        d.AddMember("happy", true, allocator);
        d.AddMember("name", "Niels", allocator);
        d.AddMember("nothing", rapidjson::Value(), allocator);

        rapidjson::Value answer(rapidjson::Type::kObjectType);
        answer.AddMember("everything", 42, allocator);
        d.AddMember("answer", answer, allocator);

        rapidjson::Value list(rapidjson::Type::kArrayType);
        list.PushBack(1, allocator);
        list.PushBack(0, allocator);
        list.PushBack(2, allocator);
        d.AddMember("list", list, allocator);

        rapidjson::Value object(rapidjson::Type::kObjectType);
        object.AddMember("currency", "USD", allocator);
        object.AddMember("value", 42.99, allocator);
        d.AddMember("object", object, allocator);

        rapidjson::StringBuffer                          buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);
        std::string json_str = buffer.GetString();
        benchmark::DoNotOptimize(json_str);
    }
}
BENCHMARK(BM_Rapidjson_Write);
