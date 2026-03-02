#pragma once

#include <benchmark/benchmark.h>
#include <string>

inline std::string generate_xml(int elements)
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
