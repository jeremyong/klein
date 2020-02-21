# Klein

[![License: MIT](https://img.shields.io/badge/License-MIT-blueviolet.svg)](https://opensource.org/licenses/MIT)
[![DOI](https://zenodo.org/badge/236777729.svg)](https://zenodo.org/badge/latestdoi/236777729)
[![Build Status](https://travis-ci.org/jeremyong/Klein.svg?branch=master)](https://travis-ci.org/jeremyong/Klein)
[![Build Status](https://ci.appveyor.com/api/projects/status/w3ug2ad08jyved8o?svg=true)](https://ci.appveyor.com/project/jeremyong/klein)

## Summary

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
- 4.2 SSE-optimized implementation (SSE2 fallback on the way)
- Requires a C++17 compiler
- Tested on Linux and Windows (Mac support is expected, but help testing is appreciated)
- Requires no third-party dependencies
- Permissively licensed

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
- Line exponentiation to generate motors
- Motor logarithm to compute the motor axis

The latter two operators can be used to efficiently implement what is traditionally
known as the spherical lerp.
