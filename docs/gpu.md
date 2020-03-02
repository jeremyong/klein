GPU support is currently provided by a single
[glsl file](https://github.com/jeremyong/klein/blob/master/glsl/klein.glsl).
This file can be pasted at the start of a shader to provide limited functionality supported by the
full C++ Klein library. The plane, line, point, rotor, translator, and motor entity structs defined
in this shader header are byte-for-byte identical to the entities as declared in C++.

Currently, the following functions are supported:

| Function                                              | Description                                       |
| ----------------------------------------------------- | ------------------------------------------------- |
| `rotor rr_mul(in rotor a, in rotor b)`                | Multiplies two rotors and returns the result      |
| `translator tt_mul(in translator a, in translator b)` | Multiplies two translators and returns the result |
| `motor mm_mul(in motor a, in motor b)`                | Multiplies two motors and returns the result      |
| `plane rotor_plane(in rotor r, in plane p)`           | Applies a rotor to a plane                        |
| `plane motor_plane(in motor m, in plane p)`           | Applies a motor to a plane                        |
| `point rotor_plane(in rotor r, in point p)`           | Applies a rotor to a point                        |
| `point motor_plane(in motor m, in point p)`           | Applies a motor to a point                        |
| `point motor_plane(in motor m)`                       | Applies a motor to the origin                     |

GPU support is verified with a C++ test suite powered by a
[shim](https://github.com/jeremyong/klein/blob/master/test/glsl_shim.hpp)
to handle vector swizzle operations and provide implementations for GLSL built-in functions. GPU
support is currently preliminary and achieving parity with seamless interoperability with the Klein
C++ headers is an ongoing objective.
