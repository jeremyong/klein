# PRStar

## Description

PRStar is a work-in-progress implementation of `P(R*_{3, 0, 1})`, aka 3D Projective Geometric
Algebra. In contrast to other GA libraries, PRStar does not attempt to generalize the metric or
dimensionality of the space. In exchange for this loss of generality, PRStar implements the
algebraic operations using the full weight of SSE (Streaming SIMD Extensions) for maximum
throughput.

## Motivation

PGA fully streamlines traditionally used quaternions, and dual-quaternions in a single algebra.
Normally, the onus is on the user to perform appropriate casts and ensure signs and memory layout
are accounted for.

## Performance Considerations

It is known that a "better" way to vectorize computation in general is to arrange the data in an SoA
layout to avoid unnecessary cross-lane arithmetic or unnecessary shuffling. PGA is unique in that
a given PGA multivector has a natural decomposition into 4 blocks of 4 floating-point quantities.
For the even sub-algebra (isomorphic to the space of dual-quaternions) also known as the _motor
algebra_, the geometric product can be densely packed and implemented efficiently using SSE.

TODO
