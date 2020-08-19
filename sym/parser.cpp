#include "parser.hpp"

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <vector>

std::ostream& operator<<(std::ostream& os, identifier const& id)
{
    std::string_view view{id.data, id.size};
    os << view;
    return os;
}

std::ostream& operator<<(std::ostream& os, element const& el)
{
    if (el.negative)
    {
        os << '-';
    }
    os << "e[0x" << std::hex << static_cast<int>(el.value) << ']';
    return os;
}

std::ostream& operator<<(std::ostream& os, token const& t)
{
    switch (t.type)
    {
    case token_type::delimiter:
        os << t.delimiter;
        break;
    case token_type::element:
        os << t.e;
        break;
    case token_type::eof:
        break;
    case token_type::identifier:
        os << t.id;
        break;
    case token_type::number:
        os << t.num;
        break;
    case token_type::op:
        os << t.op;
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, std::vector<token> const& tokens)
{
    // Display each token on a separate line and flush at the end
    for (auto&& t : tokens)
    {
        os << t << '\n';
    }
    os << std::endl;
    return os;
}

static float tokenize_number(std::string::const_iterator& it,
                             std::string::const_iterator const& end)
{
    char buf[32];
    size_t buf_size = 0;

    for (auto tmp = it; tmp != end; ++tmp)
    {
        if (buf_size > 32)
        {
            throw std::runtime_error(
                "Number with greater than 32 digits encountered");
        }

        if (std::isdigit(*tmp) || *tmp == '.')
        {
            buf[buf_size++] = *tmp;
        }
        else
        {
            break;
        }
    }
    buf[buf_size] = '\0';

    char const* float_start = buf;
    char* float_end;
    float num = std::strtof(float_start, &float_end);

    assert(float_start != float_end);
    it += float_end - float_start;
    return num;
}

static element tokenize_element(std::string::const_iterator& it,
                                std::string::const_iterator const& end,
                                algebra const& algebra_)
{
    // The iterator initially points to 'e'
    assert(*it == 'e');
    ++it;

    // Parse a digit which denotes the basis blade
    element out{};

    for (; it != end; ++it)
    {
        if (std::isdigit(*it))
        {
            uint8_t bit = *it - '0';

            if ((out.value & (1 << bit)) > 0)
            {
                throw std::runtime_error("Duplicate basis index");
            }

            // Determine if the parity flips based on the swap count
            if ((popcnt(out.value & ~((1 << bit) - 1)) & 1) == 1)
            {
                out.negative = !out.negative;
            }

            out.value |= (1 << bit);
        }
        else
        {
            break;
        }
    }

    return out;
}

static identifier tokenize_identifier(std::string::const_iterator& it,
                                      std::string::const_iterator const& end)
{
    char const* start = &*it;

    for (; it != end; ++it)
    {
        if (!std::isalnum(*it))
        {
            break;
        }
    }

    size_t size = &*it - start;
    return {start, size};
}

std::vector<token> tokenize(std::string const& input, algebra const& algebra_)
{
    std::vector<token> out;
    for (auto it = input.begin(); it != input.end();)
    {
        char c = *it;
        if (std::isspace(c))
        {
            ++it;
            continue;
        }

        token t;
        switch (c)
        {
        case '(':
        case ')':
            t.type      = token_type::delimiter;
            t.delimiter = c;
            out.emplace_back(t);
            ++it;
            continue;
        case '\0':
            // Handle early termination. Embedded nulls in the input stream
            // terminates scanning.
            t.type = token_type::eof;
            out.emplace_back(t);
            return out;
        case '+':
        // Note, the unary minus is also treated like the binary operators
        case '-':
        case '~':
        case '*':
        case '^':
        case '&':
        case '|':
            t.type = token_type::op;
            t.op   = c;
            out.emplace_back(t);
            ++it;
            continue;
        default:
            break;
        }

        if (std::isdigit(c))
        {
            t.type = token_type::number;
            t.num  = tokenize_number(it, input.end());
        }
        else if (it != input.end() - 1)
        {
            if (c == 'e' && std::isdigit(*(it + 1)))
            {
                t.type = token_type::element;
                t.e    = tokenize_element(it, input.end(), algebra_);
            }
            else
            {
                t.type = token_type::identifier;
                t.id   = tokenize_identifier(it, input.end());
            }
        }
        out.emplace_back(t);
    }

    token t;
    t.type = token_type::eof;
    out.emplace_back(t);
    return out;
}

// Parsing Grammar
//
// An expr is a sum or difference of terms
// expr := term {("+"|"-"") term} .
//
// A term is a product of factors
// term := factor {"*" factor} .
//
// A factor is an identifier with an optional unary expression
// factor := ("-"|"~") identifier (element)
//                     | number (element)
//                     | "(" expression ")" .

static mv parse_expr(std::vector<token>::const_iterator& it,
                     std::vector<token>::const_iterator end,
                     algebra const& a);

static mv parse_factor(std::vector<token>::const_iterator& it,
                       std::vector<token>::const_iterator end,
                       algebra const& a)
{
    bool negate  = false;
    bool reverse = false;
    while (it->type == token_type::op)
    {
        if (it->op == '-')
        {
            negate = !negate;
        }
        else if (it->op == '~')
        {
            reverse = !reverse;
        }
        else if (it->op != '+')
        {
            throw std::runtime_error(
                "Unexpected unary operator encountered while parsing factor");
        }
        ++it;
    }

    if (it->type == token_type::identifier || it->type == token_type::number)
    {
        mv out{a};
        poly p;
        mon m;
        float num = 1.f;
        if (it->type == token_type::identifier)
        {
            m.push(std::string{it->id.data, it->id.size});
        }
        else
        {
            num = it->num;
        }

        p.push(m, num);
        ++it;

        if (it->type == token_type::element)
        {
            element const& e = it->e;
            ++it;
            if (e.negative)
            {
                negate = !negate;
            }
            out.push(e.value, negate ? -p : p);

            return reverse ? ~out : out;
        }
        else
        {
            out.push(0, negate ? -p : p);
            return reverse ? ~out : out;
        }
    }
    else if (it->type == token_type::element)
    {
        mv out{a};
        poly p;
        mon m;
        if (it->e.negative)
        {
            negate = !negate;
        }
        p.push(m, negate ? -1.f : 1.f);

        out.push(it->e.value, p);
        ++it;
        return reverse ? ~out : out;
    }
    else if (it->type == token_type::delimiter && it->delimiter == '(')
    {
        ++it;
        mv result = parse_expr(it, end, a);
        if (it->type == token_type::delimiter && it->delimiter == ')')
        {
            ++it;
        }
        else
        {
            throw std::runtime_error(") expected after parsing expression");
        }

        if (negate)
        {
            return reverse ? -~result : -result;
        }
        else
        {
            return reverse ? ~result : result;
        }
    }
    else
    {
        throw std::runtime_error(
            "Unexpected token encountered while parsing factor");
    }
    return {a};
}

static mv parse_dot_factor(std::vector<token>::const_iterator& it,
                           std::vector<token>::const_iterator end,
                           algebra const& a)
{
    mv out = parse_factor(it, end, a);
    while (it != end && it->type == token_type::op && it->op == '|')
    {
        ++it;
        out |= parse_factor(it, end, a);
    }
    return out;
}

static mv parse_reg_factor(std::vector<token>::const_iterator& it,
                           std::vector<token>::const_iterator end,
                           algebra const& a)
{
    mv out = parse_dot_factor(it, end, a);
    while (it != end && it->type == token_type::op && it->op == '&')
    {
        ++it;
        out &= parse_dot_factor(it, end, a);
    }
    return out;
}

static mv parse_ext_factor(std::vector<token>::const_iterator& it,
                           std::vector<token>::const_iterator end,
                           algebra const& a)
{
    mv out = parse_reg_factor(it, end, a);
    while (it != end && it->type == token_type::op && it->op == '^')
    {
        ++it;
        out ^= parse_reg_factor(it, end, a);
    }
    return out;
}

static mv parse_term(std::vector<token>::const_iterator& it,
                     std::vector<token>::const_iterator end,
                     algebra const& a)
{
    mv out = parse_ext_factor(it, end, a);
    while (it != end && it->type == token_type::op && it->op == '*')
    {
        ++it;
        out *= parse_ext_factor(it, end, a);
    }
    return out;
}

static mv parse_expr(std::vector<token>::const_iterator& it,
                     std::vector<token>::const_iterator end,
                     algebra const& a)
{
    mv out = parse_term(it, end, a);

    while (it != end && it->type != token_type::eof)
    {
        if (it->type == token_type::op)
        {
            if (it->op == '+')
            {
                ++it;
                out += parse_term(it, end, a);
            }
            else if (it->op == '-')
            {
                ++it;
                out -= parse_term(it, end, a);
            }
            else
            {
                throw std::runtime_error(
                    "Unexpected operator parsing expression");
            }
        }
        else if (it->type == token_type::delimiter)
        {
            break;
        }
        else
        {
            throw std::runtime_error("Unexpected token parsing expression");
        }
    }

    return out;
}

mv parse(std::string const& input, algebra const& algebra_)
{
    std::vector<token> tokens = tokenize(input, algebra_);

    auto it = tokens.cbegin();
    return parse_expr(it, tokens.cend(), algebra_);
}