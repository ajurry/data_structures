#include <string>
#include <vector>
#include <algorithm>
#include "../include/test.hpp"

int main(int argc, const char* argv[])
{
    std::vector<std::string> to_print;

    for (int i = 1; i < argc; ++i) 
    {
        to_print.push_back(argv[i]);
    }

    test_output_class output_class;

    std::for_each(to_print.begin()
                    , to_print.end()
                    , [&](std::string text){output_class.output_text(text);});
}