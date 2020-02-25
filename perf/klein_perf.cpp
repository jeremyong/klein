#include <klein/klein.hpp>

// Run to generate llvm analysis
// clang++ bench.cpp -std=c++17 -O2 -I../public -msse4.2 -march=native -S -o - |
// llvm-mca -mcpu=btver2 | xclip

// kln::rotor rotor_composition(kln::rotor const& a, kln::rotor const& b)
// {
//     return a * b;
// }

kln::point motor_application(kln::motor const& m, kln::point const& p)
{
    return m(p);
}