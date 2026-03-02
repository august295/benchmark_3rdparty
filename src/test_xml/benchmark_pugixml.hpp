#pragma once

#include <benchmark/benchmark.h>

// pugixml
#include <pugixml.hpp>

#include "benchmark_common_xml.hpp"

static void BM_PugiXML_Parse_Args(benchmark::State& state)
{
    auto size = state.range(0);
    auto xml  = generate_xml(size);

    for (auto _ : state)
    {
        pugi::xml_document doc;
        doc.load_string(xml.c_str());
        benchmark::DoNotOptimize(doc.root());
    }
}
BENCHMARK(BM_PugiXML_Parse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});

static void BM_PugiXML_Traverse_Args(benchmark::State& state)
{
    auto size = state.range(0);
    auto xml  = generate_xml(size);

    int sum = 0;
    for (auto _ : state)
    {
        pugi::xml_document doc;
        doc.load_string(xml.c_str());
        auto root = doc.child("root");
        for (auto element : root.children("element"))
        {
            sum += element.child("value").text().as_int();
        }
    }
    benchmark::DoNotOptimize(sum);
}
BENCHMARK(BM_PugiXML_Traverse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});
