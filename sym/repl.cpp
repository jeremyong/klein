#include "repl.hpp"

#include "parser.hpp"

#include <iostream>
#include <string>

enum codes
{
    key_up   = 72,
    key_down = 80,
};

void repl::run()
{
    // Allow specification of algebra
    algebra a{3, 0, 1};
    for (std::string line; std::getline(std::cin, line);)
    {
        try
        {
            mv result = parse(line, a);
            std::cout << result << std::endl;
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}