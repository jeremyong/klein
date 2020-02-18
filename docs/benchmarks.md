The [`bench`](https://github.com/jeremyong/Klein/tree/master/bench) folder provides
a `klein_bench` executable target and a `glm_bench` executable target to compare
common operations. Some timings taken as of 2020/02/17 are reproduced below:

```
Running ./klein_bench
Run on (16 X 5000 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 256K (x8)
  L3 Unified 16384K (x1)
Load Average: 0.50, 0.77, 0.80
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_rotor_composition             1.47 ns         1.47 ns    477453168
BM_rotor_application             2.26 ns         2.26 ns    307239187
BM_rotor_matrix_conversion       3.68 ns         3.68 ns    191073706
BM_motor_composition             3.40 ns         3.40 ns    205014962
BM_motor_application             2.96 ns         2.96 ns    237085085
BM_motor_matrix_conversion       3.61 ns         3.61 ns    195147950
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
Load Average: 0.56, 0.79, 0.81
-------------------------------------------------------------------------
Benchmark                               Time             CPU   Iterations
-------------------------------------------------------------------------
BM_quat_composition                  3.22 ns         3.22 ns    219698708
BM_quat_application                  5.98 ns         5.98 ns    116975752
BM_quat_matrix_conversion            3.15 ns         3.15 ns    222991272
BM_dual_quat_composition             1.04 ns         1.04 ns    661996928
BM_dual_quat_application             5.76 ns         5.76 ns    122759985
BM_dual_quat_matrix_conversion       3.17 ns         3.17 ns    218222581
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
