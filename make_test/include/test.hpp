#pragma once
#include <string>

class test_output_class
{
    public:
        test_output_class() = default;
        std::string concatenate_strings(std::string first, std::string second) const;
};