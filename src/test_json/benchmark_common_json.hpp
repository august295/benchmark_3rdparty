#pragma once

#include <benchmark/benchmark.h>
#include <string>
#include <fstream>
#include <sstream>

inline std::string read_file_to_string(const std::string& filename)
{
    std::ifstream      f(filename, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

inline std::ifstream::pos_type get_file_size(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary | std::ios::ate);
    return in.tellg();
}
