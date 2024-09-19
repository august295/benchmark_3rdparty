#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include <benchmark/benchmark.h>

#include <nlohmann/json.hpp>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

/**
 * @brief json 测试
 *  1. parse JSON from file
 *  2. parse JSON from string
 *  3. write
 */
static void bench_json_parse_file(benchmark::State& state, const std::string& filename)
{
    while (state.KeepRunning())
    {
        try
        {
            state.PauseTiming();
            auto* f = new std::ifstream(filename);
            auto* j = new nlohmann::json();
            state.ResumeTiming();

            *j = nlohmann::json::parse(*f);

            state.PauseTiming();
            delete f;
            delete j;
            state.ResumeTiming();
        }
        catch (const std::exception&)
        {
        }
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    state.SetBytesProcessed(state.iterations() * file.tellg());
}
BENCHMARK_CAPTURE(bench_json_parse_file, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(bench_json_parse_file, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(bench_json_parse_file, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(bench_json_parse_file, 1MB, "json/1MB.json");

static void bench_json_parse_string(benchmark::State& state, const std::string& filename)
{
    std::ifstream f(filename);
    std::string   str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    while (state.KeepRunning())
    {
        try
        {
            state.PauseTiming();
            auto* j = new nlohmann::json();
            state.ResumeTiming();

            *j = nlohmann::json::parse(str);

            state.PauseTiming();
            delete j;
            state.ResumeTiming();
        }
        catch (const std::exception&)
        {
        }
    }

    state.SetBytesProcessed(state.iterations() * str.size());
}
BENCHMARK_CAPTURE(bench_json_parse_string, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(bench_json_parse_string, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(bench_json_parse_string, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(bench_json_parse_string, 1MB, "json/1MB.json");

static void bench_json_write(benchmark::State& state)
{
    for (auto _ : state)
    {
        // create an empty structure (null)
        nlohmann::json j;

        // add a number that is stored as double (note the implicit conversion of j to an object)
        j["pi"] = 3.141;

        // add a Boolean that is stored as bool
        j["happy"] = true;

        // add a string that is stored as std::string
        j["name"] = "Niels";

        // add another null object by passing nullptr
        j["nothing"] = nullptr;

        // add an object inside the object
        j["answer"]["everything"] = 42;

        // add an array that is stored as std::vector (using an initializer list)
        j["list"] = {1, 0, 2};

        // add another object (using an initializer list of pairs)
        j["object"] = {{"currency", "USD"}, {"value", 42.99}};

        std::string json_str = j.dump(4);
    }
}
BENCHMARK_CAPTURE(bench_json_write, json_dump);

/**
 * @brief rapidjson 测试
 *  1. parse JSON from file
 *  2. parse JSON from string
 *  3. write
 */
static void bench_rapidjson_parse_file(benchmark::State& state, const std::string& filename)
{
    while (state.KeepRunning())
    {
        try
        {
            state.PauseTiming();
            auto* f   = new std::ifstream(filename);
            auto* isw = new rapidjson::IStreamWrapper(*f);
            auto* j   = new rapidjson::Document();
            state.ResumeTiming();

            j->ParseStream(*isw);

            state.PauseTiming();
            delete f;
            delete isw;
            delete j;
            state.ResumeTiming();
        }
        catch (const std::exception&)
        {
        }
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    state.SetBytesProcessed(state.iterations() * file.tellg());
}
BENCHMARK_CAPTURE(bench_rapidjson_parse_file, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(bench_rapidjson_parse_file, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(bench_rapidjson_parse_file, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(bench_rapidjson_parse_file, 1MB, "json/1MB.json");

static void bench_rapidjson_parse_string(benchmark::State& state, const std::string& filename)
{
    std::ifstream f(filename);
    std::string   str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    while (state.KeepRunning())
    {
        try
        {
            state.PauseTiming();
            auto* j = new rapidjson::Document();
            state.ResumeTiming();

            j->Parse(str.c_str());

            state.PauseTiming();
            delete j;
            state.ResumeTiming();
        }
        catch (const std::exception&)
        {
        }
    }

    state.SetBytesProcessed(state.iterations() * str.size());
}
BENCHMARK_CAPTURE(bench_rapidjson_parse_string, 64KB, "json/64KB.json");
BENCHMARK_CAPTURE(bench_rapidjson_parse_string, 256KB, "json/256KB.json");
BENCHMARK_CAPTURE(bench_rapidjson_parse_string, 512KB, "json/512KB.json");
BENCHMARK_CAPTURE(bench_rapidjson_parse_string, 1MB, "json/1MB.json");

static void bench_rapidjson_write(benchmark::State& state)
{
    for (auto _ : state)
    {
        // create an empty structure (null)
        rapidjson::Document j(rapidjson::Type::kObjectType);
        auto&               allocator = j.GetAllocator();

        // add a number that is stored as double (note the implicit conversion of j to an object)
        j.AddMember("pi", 3.141, allocator);

        // add a Boolean that is stored as bool
        j.AddMember("happy", true, allocator);

        // add a string that is stored as std::string
        j.AddMember("name", "Niels", allocator);

        // add another null object by passing nullptr
        j.AddMember("nothing", rapidjson::Value(), allocator);

        // add an object inside the object
        rapidjson::Value answer(rapidjson::Type::kObjectType);
        answer.AddMember("everything", 42, allocator);
        j.AddMember("answer", answer, allocator);

        // add an array that is stored as std::vector (using an initializer list)
        rapidjson::Value list(rapidjson::Type::kArrayType);
        list.PushBack(1, allocator);
        list.PushBack(0, allocator);
        list.PushBack(2, allocator);
        j.AddMember("list", list, allocator);

        // add another object (using an initializer list of pairs)
        rapidjson::Value object(rapidjson::Type::kObjectType);
        object.AddMember("currency", "USD", allocator);
        object.AddMember("value", 42.99, allocator);
        j.AddMember("object", object, allocator);

        rapidjson::StringBuffer                          buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        j.Accept(writer);
        std::string json_str = buffer.GetString();
    }
}
BENCHMARK_CAPTURE(bench_rapidjson_write, json_dump);

BENCHMARK_MAIN();