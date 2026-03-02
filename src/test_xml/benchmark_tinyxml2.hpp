#pragma once

#include <benchmark/benchmark.h>

// TinyXML-2
#include <tinyxml2.h>

#include "benchmark_common_xml.hpp"

static void BM_TinyXML2_Parse_Args(benchmark::State& state)
{
    auto size = state.range(0);
    auto xml  = generate_xml(size);

    for (auto _ : state)
    {
        tinyxml2::XMLDocument doc;
        doc.Parse(xml.c_str());
        benchmark::DoNotOptimize(doc.RootElement());
    }
}
BENCHMARK(BM_TinyXML2_Parse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});

static void BM_TinyXML2_Traverse_Args(benchmark::State& state)
{
    auto size = state.range(0);
    auto xml  = generate_xml(size);

    int sum = 0;
    for (auto _ : state)
    {
        tinyxml2::XMLDocument doc;
        doc.Parse(xml.c_str());
        auto root = doc.RootElement();
        for (auto element = root->FirstChildElement("element"); element; element = element->NextSiblingElement("element"))
        {
            sum += std::stoi(element->FirstChildElement("value")->GetText());
        }
    }
    benchmark::DoNotOptimize(sum);
}
BENCHMARK(BM_TinyXML2_Traverse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});
