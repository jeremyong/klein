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
        if (line.empty())
        {
            std::cout << std::endl;
            continue;
        }

        // Skip lines that only contain whitespace or commas
        bool should_parse  = false;
        bool issue_command = false;
        for (auto c : line)
        {
            if (std::isspace(c))
            {
                continue;
            }
            else if (c == '#')
            {
                // Lines that begin with a # are comments
                // Echo them in the output
                std::cout << line;
                break;
            }
            else if (c == '.')
            {
                // Lines that start with a . are commands
                issue_command = true;
                break;
            }
            else
            {
                should_parse = true;
            }
        }

        if (issue_command)
        {
            // TODO replace with an actual command parser
            if (line == ".break")
            {
                break_lines = !break_lines;
            }
            continue;
        }
        else if (!should_parse)
        {
            std::cout << std::endl;
            continue;
        }

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