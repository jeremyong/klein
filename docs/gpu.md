GPU support is currently provided by a single
[glsl file](https://github.com/jeremyong/klein/blob/master/glsl/klein.glsl).
This file can be pasted at the start of a shader to provide limited functionality supported by the
full C++ Klein library. The `kln_plane`, `kln_line`, `kln_point`, `kln_rotor`, and `kln_motor` entity structs defined
in this shader header are byte-for-byte identical to their C++ counterparts.

Currently, the following functions are supported:

| Function                                                           | Description                                       |
| ------------------------------------------------------------------ | ------------------------------------------------- |
| `kln_rotor kln_mul(in kln_rotor a, in kln_rotor b)`                | Multiplies two rotors and returns the result      |
| `kln_translator kln_mul(in kln_translator a, in kln_translator b)` | Multiplies two translators and returns the result |
| `kln_motor kln_mul(in kln_motor a, in kln_motor b)`                | Multiplies two motors and returns the result      |
| `kln_plane kln_apply(in kln_rotor r, in kln_plane p)`              | Applies a rotor to a plane                        |
| `kln_plane kln_apply(in kln_motor m, in kln_plane p)`              | Applies a motor to a plane                        |
| `kln_point kln_apply(in kln_rotor r, in kln_point p)`              | Applies a rotor to a point                        |
| `kln_point kln_apply(in kln_motor m, in kln_point p)`              | Applies a motor to a point                        |
| `kln_point kln_apply(in kln_motor m)`                              | Applies a motor to the origin                     |

GPU support is verified with a C++ test suite powered by a
[shim](https://github.com/jeremyong/klein/blob/master/test/glsl_shim.hpp)
to handle vector swizzle operations and provide implementations for GLSL built-in functions. GPU
support is currently preliminary and achieving parity with seamless interoperability with the Klein
C++ headers is an ongoing objective.
