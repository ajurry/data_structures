#include "../include/test.hpp"
#include <iostream>
#include <string>

void test_output_class::output_text(std::string& out) const
{
    std::cout << "Output: " << out << std::endl;
}