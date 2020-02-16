The [`bench`](https://github.com/jeremyong/Klein/tree/master/bench) folder provides
a `klein_bench` executable target and a `glm_bench` executable target to compare
common operations. Some timings taken as of 2020/02/14 are reproduced below:

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