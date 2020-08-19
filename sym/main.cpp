#include "ga.hpp"
#include "parser.hpp"
#include "repl.hpp"

int main(int argc, char** argv)
{
    // std::string test = "4e0 + (b + c) * e102";
    // std::string test = "(3e0 + 3e012) + (3e0 - 3e012)";
    // algebra pga{3, 0, 1};
    // std::cout << tokenize(test, a);
    // mv mv1 = parse("(e23 + 2e012) * (2 - 3e01)", pga);
    // std::cout << mv1 << std::endl;
    repl r;
    r.run();
    return 0;
}