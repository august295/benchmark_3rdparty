#include <fstream>
#include <vector>

#include <benchmark/benchmark.h>

// TinyXML-2
#include <tinyxml2.h>

// pugixml
#include <pugixml.hpp>

// 生成测试用 XML 数据
std::string generate_xml(int elements)
{
    std::string xml = "<?xml version=\"1.0\"?><root>";
    for (int i = 0; i < elements; ++i)
    {
        xml += "<element id=\"" + std::to_string(i) + "\">";
        xml += "<value>" + std::to_string(i * 10) + "</value>";
        xml += "</element>";
    }
    xml += "</root>";
    return xml;
}

// 遍历测试
template <typename T>
void traverse_xml_benchmark(benchmark::State& state, T& doc);

// 通用的遍历逻辑
template <>
void traverse_xml_benchmark<pugi::xml_document>(benchmark::State& state, pugi::xml_document& doc)
{
    int sum = 0;
    for (auto _ : state)
    {
        auto root = doc.child("root");
        for (auto element : root.children("element"))
        {
            sum += element.child("value").text().as_int();
        }
    }
    benchmark::DoNotOptimize(sum);
}

template <>
void traverse_xml_benchmark<tinyxml2::XMLDocument>(benchmark::State& state, tinyxml2::XMLDocument& doc)
{
    int sum = 0;
    for (auto _ : state)
    {
        auto root = doc.RootElement();
        for (auto element = root->FirstChildElement("element"); element; element = element->NextSiblingElement("element"))
        {
            sum += std::stoi(element->FirstChildElement("value")->GetText());
        }
    }
    benchmark::DoNotOptimize(sum);
}

// TinyXML-2 解析测试
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

// TinyXML-2 遍历测试
static void BM_TinyXML2_Traverse_Args(benchmark::State& state)
{
    auto size = state.range(0);
    auto xml  = generate_xml(size);

    tinyxml2::XMLDocument doc;
    doc.Parse(xml.c_str());
    traverse_xml_benchmark(state, doc);
}
BENCHMARK(BM_TinyXML2_Traverse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});

// pugixml 解析测试
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

// pugixml 遍历测试
static void BM_PugiXML_Traverse_Args(benchmark::State& state)
{
    auto size = state.range(0);
    auto xml  = generate_xml(size);

    pugi::xml_document doc;
    doc.load_string(xml.c_str());
    traverse_xml_benchmark(state, doc);
}
BENCHMARK(BM_PugiXML_Traverse_Args)
    ->Args({100})
    ->Args({1000})
    ->Args({10000});

BENCHMARK_MAIN();