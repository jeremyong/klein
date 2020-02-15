# Klein

## Description

Klein is an implementation of `P(R*_{3, 0, 1})`, aka 3D Projective Geometric Algebra.
It is designed for applications that demand high-throughput (animation libraries,
kinematic solvers, etc). In contrast to other GA libraries, Klein does not attempt to
generalize the metric or dimensionality of the space. In exchange for this loss of generality,
Klein implements the algebraic operations using the full weight of SSE (Streaming
SIMD Extensions) for maximum throughput.

## Requirements

- Machine with a processor that supports SSE4.2 or later (has ~97% market penetration)
- C++17 compliant compiler

## Usage

You have two options to use Klein in your codebase. First, you can simply copy the contents of the
`public` folder somewhere in your include path. Alternatively, you can include this entire project
in your source tree, and using cmake, `add_subdirectory(Klein)` and link the `klein` interface
target.

In your code, there is a single header to include via `#include <klein/klein.hpp>`, at which point
you can create planes, points, lines, ideal lines, bivectors, motors, directions, and use their
operations. As a simple demo, here are a couple common routines.

```c++
#include <klein/klein.cpp>

// Shows how to construct a point. There isn't much to it.
kln::point construct_point(float x, float y, float z)
{
    return kln::point{x, y, z};
}

// Shows how to construct a plane. Similarly unexciting.
kln::plane construct_point(float x, float y, float z, float d)
{
    // d corresponds to the displacement from the origin.
    return kln::plane{x, y, z, d};
}

// Shows how to construct a rotor.
kln::rotor construct_rotor(float ang_rad, float x, float y, float z)
{
    // Provide the angle of rotation and the axis.
    // The rotor constructed in this way is normalized.
    return kln::rotor{ang_rad, x, y, z};
}

// Shows how to construct a translator (aka displacement)
kln::translator construct_translator(float d, float x, float y, float z)
{
    // As with the rotor, the magnitude of the axis is normalized
    return kln::translator{ang_rad, x, y, z};
}

// Shows how we can combine a rotation and translation to produce a motor
kln::motor construct_motor(kln::rotor const& r, kln::translator const& t)
{
    // Because the rotor and translator perform rotations around orthogonal
    // bivectors (a rotor rotates around a Euclidean line, and a translator
    // "rotates" around an ideal line), their operations commute. The two
    // can be multiplied in any order to construct a motor that combines
    // both the rotation and the translation.
    return r * t;
}

// Rotors can be applied to points
kln::point rotate_point(kln::rotor const& r, kln::point const& p)
{
    return r(p);
}

// Rotors can also be applied to planes
kln::plane rotate_plane(kln::rotor const& r, kln::plane const& p)
{
    return r(p);
}

// Motors can be applied in the same way
kln::point motorize_point(kln::motor const& m, kln::point const& p)
{
    return m(p);
}

// Motors can be applied in the same way
kln::plane motorize_plane(kln::motor const& m, kln::plane const& p)
{
    return m(p);
}

// We can multiple motors, rotors, and translators together to create
// composite actions. Here we combine the effect of two motors.
kln::motor compose_two_motors(kln::motor const& m1, kln::motor const& m2)
{
    // The resulting motor has an action equivalent to applying m1 first, followed by m2.
    return m2 * m1;
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

Here are some timings taken as of 2020/02/14:

```
Running ./klein_bench
Run on (16 X 5000 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 256K (x8)
  L3 Unified 16384K (x1)
Load Average: 0.73, 0.84, 0.66
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_rotor_composition              209 ns          211 ns      3356746
BM_rotor_application              207 ns          209 ns      3353725
BM_rotor_matrix_conversion        206 ns          208 ns      3358056
BM_motor_composition              210 ns          211 ns      3313448
BM_motor_application              206 ns          208 ns      3346123
BM_motor_matrix_conversion        208 ns          210 ns      3328768
```

For comparison, an equivalent benchmark for the well-optimized GLM is provided:

```
Running ./glm_bench
Run on (16 X 5000 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 256K (x8)
  L3 Unified 16384K (x1)
Load Average: 0.81, 0.85, 0.67
-------------------------------------------------------------------------
Benchmark                               Time             CPU   Iterations
-------------------------------------------------------------------------
BM_quat_composition                   210 ns          212 ns      3290850
BM_quat_application                   212 ns          213 ns      3268476
BM_quat_matrix_conversion             208 ns          209 ns      3303599
BM_quat_composition                   211 ns          213 ns      3292393
BM_dual_quat_application              219 ns          221 ns      3165149
BM_dual_quat_matrix_conversion        214 ns          215 ns      3249413
```

These results should _not_ be interpreted to mean that Klein is unilaterally superior
performance-wise to GLM or any other such major library. However, it is a good indicator that Klein
is at the very least competitive with competing libraries that do not have the benefits of geometric
algebraic underpinnings.

As with all benchmarks, there will always be some measurement noise, and the above timings will
be accurate in situations where the application is not memory bound. However, in such a case, the
library implementation will be less critical so it makes for a less interesting benchmark. The klein
implementation of motors and rotors are largely shared, and motors only require a few additional
instructions so the timing of motors is only a hair slower than rotors.

Frequency scaling was disabled during these tests to avoid pathological measurement errors that
occur when the CPU ramps up in the initial part of an SSE heavy benchmark. In addition, both the
klein and glm benchmark programs were compiled with -O2 under GCC 9.1 with SSE4.2 enabled.

# klein_shell

A simple command line REPL (Read Eval Print Loop) is provided to perform
symbolic evaluation of GA expressions. This is a work-in-progress but is already used to help
compute expressions needed to optimize Klein.

To see it in use, a sample script has been
[provided](https://github.com/jeremyong/Klein/blob/master/scripts/demo.klein). To invoke the script, on a
command prompt, run `cat demo.klein | path/to/klein_shell`.

The `klein_shell` executable can also be used as a standalone utility (without piping text in via
STDIN). The library it is built on is also provided here in the `src` folder.

# References

Klein is deeply indebted to several members of the GA community and their work. Beyond the works
cited here, the author stands of the shoulders of giants (Felix _Klein_, Sophus Lie, Arthur Cayley,
William Rowan Hamilton, Julius Plücker, and William Kingdon Clifford, among others).

<a id="1">[1]</a>
Gunn, Charles G. (2019).
Projective geometric algebra: A new framework for doing euclidean geometry.
[arXiv link](https://arxiv.org/abs/1901.05873)

<a id="2">[2]</a>
Steven De Keninck and Charles Gunn. (2019).
SIGGRAPH 2019 Geometric Algebra Course.
[youtube link](https://www.youtube.com/watch?v=tX4H_ctggYo)

<a id="3">[3]</a>
Leo Dorst, Daniel Fontijne, Stephen Mann. (2007)
Geometric Algebra for Computer Science.
Burlington, MA: Morgan Kaufmann Publishers Inc.

## TODO

- Provide a fallback for SSE2 in case SSE4.1 isn't available
- Sandwich operator for lines
- Exterior product
- Norms
