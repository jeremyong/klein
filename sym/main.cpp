#include "repl.hpp"

int main(int argc, char** argv)
{
    // std::string test = "4e0 + (b + c) * e102";
    // algebra a{3, 0, 1};
    // std::cout << tokenize(test, a);
    // mv m = parse(test, a);
    repl r;
    r.run();
    return 0;
}