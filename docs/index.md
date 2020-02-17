# Klein

[![License: MIT](https://img.shields.io/badge/License-MIT-blueviolet.svg)](https://opensource.org/licenses/MIT)
[![DOI](https://zenodo.org/badge/236777729.svg)](https://zenodo.org/badge/latestdoi/236777729)

[Klein](https://github.com/jeremyong/Klein) is an implementation of $\mathbf{P}(\mathbb{R}^*_{3, 0, 1})$, aka 3D Projective Geometric Algebra.
It is designed for applications that demand high-throughput (animation libraries,
kinematic solvers, etc). In contrast to other GA libraries, Klein does not attempt to
generalize the metric or dimensionality of the space. In exchange for this loss of generality,
Klein implements the algebraic operations using the full weight of SSE (Streaming
SIMD Extensions) for maximum throughput. Klein's performance is fully competitive with state of the
art kinematic and math libraries built with traditional vector and quaternion formulations.

Summary

- Geometric computing library suitable for use with realtime graphics and animation applications
- Header-only core libary with an optional lightweight symbolic computer algebra system
- 4.2 SSE-optimized implementation (SSE2 fallback on the way)
- Requires a C++17 compiler (C++11/14 fallback on the way)
- Tested on Linux and Windows (Mac support is expected, but help testing is appreciated)

Supported entities:

- Points
- Directions
- Lines
- Ideal lines
- Planes
- Rotors
- Translators
- Motors

Supported operations:

- Geometric product (used to compose group actions)
- Exterior product (used to meet entities)
- Regressive product (used to join entities)
- Sandwich operators (defined via the call operator on rotors, translators, and motors)
- Standard arithmetic operations
- Line exponentiation to generate motors
- Motor logarithm to compute the motor axis

The latter two operators can be used to efficiently implement what is traditionally
known as the spherical lerp.
