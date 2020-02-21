# [Klein](https://jeremyong.com/klein)

[![License: MIT](https://img.shields.io/badge/License-MIT-blueviolet.svg)](https://opensource.org/licenses/MIT)
[![DOI](https://zenodo.org/badge/236777729.svg)](https://zenodo.org/badge/latestdoi/236777729)
[![Build Status](https://travis-ci.org/jeremyong/klein.svg?branch=master)](https://travis-ci.org/jeremyong/klein)
[![Build Status](https://ci.appveyor.com/api/projects/status/w3ug2ad08jyved8o?svg=true)](https://ci.appveyor.com/project/jeremyong/klein)
[![Coverity Status](https://img.shields.io/coverity/scan/20402.svg)](https://scan.coverity.com/projects/jeremyong-klein)

## Description

Klein is an implementation of `P(R*_{3, 0, 1})`, aka 3D Projective Geometric Algebra.
It is designed for applications that demand high-throughput (animation libraries,
kinematic solvers, etc). In contrast to other GA libraries, Klein does not attempt to
generalize the metric or dimensionality of the space. In exchange for this loss of generality,
Klein implements the algebraic operations using the full weight of SSE (Streaming
SIMD Extensions) for maximum throughput.

## Requirements

- Machine with a processor that supports SSE4.2 or later (has ~97% market penetration)
- C++17 compliant compiler (tested with GCC 9.2.1, Clang 9.0.1, and Visual Studio 2019)

## Usage

You have two options to use Klein in your codebase. First, you can simply copy the contents of the
`public` folder somewhere in your include path. Alternatively, you can include this entire project
in your source tree, and using cmake, `add_subdirectory(Klein)` and link the `klein` interface
target.

In your code, there is a single header to include via `#include <klein/klein.hpp>`, at which point
you can create planes, points, lines, ideal lines, bivectors, motors, directions, and use their
operations. Please refer to the [project site](https://jeremyong.com/klein) for the most up-to-date
documentation.

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

# References

Klein is deeply indebted to several members of the GA community and their work. Beyond the works
cited here, the author stands of the shoulders of giants (Felix _Klein_, Sophus Lie, Arthur Cayley,
William Rowan Hamilton, Julius Plücker, and William Kingdon Clifford, among others).

<a id="1">[1]</a>
Gunn, Charles G. (2019).
Course notes Geometric Algebra for Computer Graphics, SIGGRAPH 2019.
[arXiv link](https://arxiv.org/abs/2002.04509)

<a id="2">[2]</a>
Steven De Keninck and Charles Gunn. (2019).
SIGGRAPH 2019 Geometric Algebra Course.
[youtube link](https://www.youtube.com/watch?v=tX4H_ctggYo)

<a id="3">[3]</a>
Leo Dorst, Daniel Fontijne, Stephen Mann. (2007)
Geometric Algebra for Computer Science.
Burlington, MA: Morgan Kaufmann Publishers Inc.
