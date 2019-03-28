#pragma once
#include <string>

class test_output_class
{
    public:
        test_output_class() = default;
        void output_text(std::string& out) const;
};