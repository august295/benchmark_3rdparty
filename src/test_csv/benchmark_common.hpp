#pragma once

#include <sstream>
#include <string>

inline std::string generate_csv(int rows, int cols)
{
    std::stringstream ss;
    for (int j = 0; j < cols; ++j)
    {
        ss << "col" << j;
        if (j < cols - 1)
            ss << ",";
    }
    ss << "\n";

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            ss << i * cols + j;
            if (j < cols - 1)
                ss << ",";
        }
        ss << "\n";
    }
    return ss.str();
}
