#include "../include/test.hpp"
#include <iostream>
#include <string>

std::string test_output_class::concatenate_strings(
    std::string first
    , std::string second
) const    
{
    return first + second;
}