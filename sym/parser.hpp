#pragma once

#include "ga.hpp"

#include <iostream>
#include <vector>

enum class token_type
{
    element,
    number,
    identifier,
    delimiter,
    op,
    eof
};

struct identifier
{
    char const* data;
    size_t size;
};

struct element
{
    uint8_t value;
    bool negative;
};

struct token
{
    union
    {
        element e;
        float num;
        identifier id;
        char delimiter;
        char op;
    };
    token_type type;
};

// iostream operators for convenient debugging
std::ostream& operator<<(std::ostream& os, identifier const& id);
std::ostream& operator<<(std::ostream& os, element const& el);
std::ostream& operator<<(std::ostream& os, token const& t);
std::ostream& operator<<(std::ostream& os, std::vector<token> const& tokens);

std::vector<token> tokenize(std::string const& input, algebra const& algebra_);

mv parse(std::string const& input, algebra const& a);
