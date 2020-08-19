![Klein](./img/android-chrome-192x192.png)

# Klein

[![License: MIT](https://img.shields.io/badge/License-MIT-blueviolet.svg)](https://opensource.org/licenses/MIT)
[![DOI](https://zenodo.org/badge/236777729.svg)](https://zenodo.org/badge/latestdoi/236777729)
[![Build Status](https://travis-ci.org/jeremyong/Klein.svg?branch=master)](https://travis-ci.org/jeremyong/Klein)
[![Build Status](https://ci.appveyor.com/api/projects/status/w3ug2ad08jyved8o?svg=true)](https://ci.appveyor.com/project/jeremyong/klein)
[![Coverity Status](https://img.shields.io/coverity/scan/20402.svg)](https://scan.coverity.com/projects/jeremyong-klein)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5908bd446f3d4bb0bb1fd2e0808cb8a1)](https://www.codacy.com/manual/jeremyong/klein?utm_source=github.com&utm_medium=referral&utm_content=jeremyong/klein&utm_campaign=Badge_Grade)

Do you need to do any of the following? Quickly? _Really_ quickly even?

- Projecting points onto lines, lines to planes, points to planes?
- Measuring distances and angles between points, lines, and planes?
- Rotate or translate points, lines, and planes?
- Perform smooth rigid body transforms? Interpolate them smoothly?
- Construct lines from points? Planes from points? Planes from a line and a point?
- Intersect planes to form lines? Intersect a planes and lines to form points?

If so, then Klein is the library for you!

## Feature Summary

[Klein](https://github.com/jeremyong/Klein) is an implementation of $\mathbf{P}(\mathbb{R}^*_{3, 0, 1})$, aka 3D Projective Geometric Algebra.
It is designed for applications that demand high-throughput (animation libraries,
kinematic solvers, etc). In contrast to other GA libraries, Klein does not attempt to
generalize the metric or dimensionality of the space. In exchange for this loss of generality,
Klein implements the algebraic operations using the full weight of SSE (Streaming
SIMD Extensions) for maximum throughput. Klein's performance is fully competitive with state of the
art kinematic and math libraries built with traditional vector and quaternion formulations.

!!! tip

    **Knowledge of Geometric Algebra is NOT required to benefit from the library**, but
    familiarity can ease the learning curve of the API somewhat, as the operators in
    Geometric Algebra map cleanly to geometric operations.

- Geometric computing library suitable for use with realtime graphics and animation applications
- Header-only core libary with an optional lightweight symbolic computer algebra system
- SSE3 or SSE4.1-optimized implementations
- Tested on Linux, MacOS, and Windows
- Requires no third-party dependencies
- Permissively licensed

## Frequently tested compilers

- GCC 9.2.1 on Linux
- Clang 9.0.1 on Linux
- Visual Studio 2019 on Windows 10
- Xcode 11.3 on MacOS

## Supported entities

- Points
- Directions
- Lines
- Ideal lines
- Planes
- Rotors
- Translators
- Motors

## Supported operations

- Geometric product (used to compose group actions)
- Exterior product (used to meet entities)
- Regressive product (used to join entities)
- Conjugation (aka "sandwich") operators (defined via the call operator on planes, rotors, translators, and motors)
- Inner product (used for metric measurements and to project entities)
- Standard arithmetic operations
- Motor logarithm to compute the motor axis
- Line exponentiation to generate motors
- Rotor logarithm to compute the rotor axis (also referred to as a `branch`)
- Branch exponentiation to generate rotors

The spherical interpolation operation "slerp" can be implemented easily in terms of the rotor or
motor logarithm, depending on what is needed.
