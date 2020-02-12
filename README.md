# Klein

## Description

Klein is an implementation of `P(R*_{3, 0, 1})`, aka 3D Projective Geometric Algebra.
It is designed for applications that demand high-throughput (animation libraries,
kinematic solvers, etc). In contrast to other GA libraries, Klein does not attempt to
generalize the metric or dimensionality of the space. In exchange for this loss of generality,
Klein implements the algebraic operations using the full weight of SSE (Streaming
SIMD Extensions) for maximum throughput.

## Requirements

- Machine with a processor that supports SSE4.1 or later (has ~97% market penetration)
- C++17 compliant compiler

## Usage

You have two options to use Klein in your codebase. First, you can simply copy the contents of the
`public` folder somewhere in your include path. Alternatively, you can include this entire project
in your source tree, and using cmake, `add_subdirectory(Klein)` and link the `klein` interface
target.

In your code, there is a single header to include via `#include <klein/klein.hpp>`, at which point
you can create planes, points, lines, ideal lines, bivectors, motors, directions, and use their
operations. As a simple demo, here's a routine that applies a motor to a point:

```c++
#include <klein/klein.cpp>

kln::point motorize_point(kln::motor const& m, kln::point const& p)
{
    return m(p);
}
```

## Motivation

PGA fully streamlines traditionally used quaternions, and dual-quaternions in a single algebra.
Normally, the onus is on the user to perform appropriate casts and ensure signs and memory layout
are accounted for. Here, all types are unified within the geometric algebra,
and operations such as quaternion _ dual-quat (rotor _ motor) compositions make sense.

## Performance Considerations

It is known that a "better" way to vectorize computation in general is to arrange the data in an SoA
layout to avoid unnecessary cross-lane arithmetic or unnecessary shuffling. PGA is unique in that
a given PGA multivector has a natural decomposition into 4 blocks of 4 floating-point quantities.
For the even sub-algebra (isomorphic to the space of dual-quaternions) also known as the _motor
algebra_, the geometric product can be densely packed and implemented efficiently using SSE.

# klein_shell

A simple command line REPL (Read Eval Print Loop) is provided to perform
symbolic evaluation of GA expressions. This is a work-in-progress but is already used to help
compute expressions needed to optimize Klein.

To see it in use, a sample script has been
[provided](https://github.com/jeremyong/Klein/blob/master/demo.klein). To invoke the script, on a
command prompt, run `cat demo.klein | path/to/klein_shell`.

The `klein_shell` executable can also be used as a standalone utility (without piping text in via
STDIN). The library it is built on is also provided here in the `src` folder.

## TODO

- Provide a fallback for SSE2 in case SSE4.1 isn't available
- Sandwich operator for lines
- Exterior product
- Rotors
- Exp/Log
- Norms
- Matrix conversion
