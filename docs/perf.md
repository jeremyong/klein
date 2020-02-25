Performance of SSE code is tricky to estimate, especially in real-world scenarios. Properties of
code tested in a microbenchmark do not transfer well to the wild. For example, aggressive register
usage generally translates to better microbenchmark results, but may not result in faster running
"real-world" applications.

On this page, assembly snippets for common routines are provided for inspection, as well as analysis
produced by [llvm-mca](https://llvm.org/docs/CommandGuide/llvm-mca.html). Users are encouranged to
_benchmark their own code_ and create an issue if a performance issue is believed to have been
discovered. The analysis provided by LLVM-MCA cannot be used as a proxy for predicting performance,
although it is a useful tool to compare alternatives.

Only a few routines are provided here as an indicator of the performance and implementation
characteristics of the rest of the code. To understand the implications of the various counters and
resource estimates provided, please refer to the excellent analysis provided at [uops.info](https://uops.info/).

## Rotor Composition

```c++
kln::rotor ab(kln::rotor const& a, kln::rotor const& b)
{
    return a * b;
}
```

??? tip "Klein LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      2200
    Total Cycles:      1218
    Total uOps:        2300

    Dispatch Width:    2
    uOps Per Cycle:    1.89
    IPC:               1.81
    Block RThroughput: 11.5


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      1     0.50                        movq	%rdi, %rax
     1      5     1.00    *                   vmovaps	(%rsi), %xmm0
     1      1     0.50                        vbroadcastss	%xmm0, %xmm1
     1      5     1.00    *                   vmovaps	(%rdx), %xmm2
     1      2     1.00                        vmulps	%xmm2, %xmm1, %xmm1
     1      1     0.50                        vpermilps	$121, %xmm0, %xmm3
     1      1     0.50                        vpermilps	$157, %xmm2, %xmm4
     1      2     1.00                        vmulps	%xmm4, %xmm3, %xmm3
     1      3     1.00                        vsubps	%xmm3, %xmm1, %xmm1
     1      1     0.50                        vpermilps	$230, %xmm0, %xmm3
     1      1     0.50                        vpermilps	$2, %xmm2, %xmm4
     1      2     1.00                        vmulps	%xmm4, %xmm3, %xmm3
     1      1     0.50                        vpermilps	$159, %xmm0, %xmm0
     1      1     0.50                        vpermilps	$123, %xmm2, %xmm2
     1      2     1.00                        vmulps	%xmm2, %xmm0, %xmm0
     1      3     1.00                        vaddps	%xmm0, %xmm3, %xmm0
     1      1     0.50                        movl	$-2147483648, %ecx
     2      8     0.50                        vmovd	%ecx, %xmm2
     1      1     0.50                        vxorps	%xmm2, %xmm0, %xmm0
     1      3     1.00                        vaddps	%xmm0, %xmm1, %xmm0
     1      1     1.00           *            vmovaps	%xmm0, (%rdi)
     1      4     1.00                  U     retq


    Resources:
    [0]   - JALU0
    [1]   - JALU1
    [2]   - JDiv
    [3]   - JFPA
    [4]   - JFPM
    [5]   - JFPU0
    [6]   - JFPU1
    [7]   - JLAGU
    [8]   - JMul
    [9]   - JSAGU
    [10]  - JSTC
    [11]  - JVALU0
    [12]  - JVALU1
    [13]  - JVIMUL


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]
    1.50   1.50    -     9.01   8.99   9.50   9.50   3.00    -     1.00   1.00    -      -      -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
    0.50   0.50    -      -      -      -      -      -      -      -      -      -      -      -     movq	%rdi, %rax
     -      -      -     0.94   0.06   0.96   0.04   1.00    -      -      -      -      -      -     vmovaps	(%rsi), %xmm0
     -      -      -     0.97   0.03   0.48   0.52    -      -      -      -      -      -      -     vbroadcastss	%xmm0, %xmm1
     -      -      -     0.94   0.06   0.47   0.53   1.00    -      -      -      -      -      -     vmovaps	(%rdx), %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm2, %xmm1, %xmm1
     -      -      -     0.03   0.97   0.52   0.48    -      -      -      -      -      -      -     vpermilps	$121, %xmm0, %xmm3
     -      -      -     1.00    -     0.53   0.47    -      -      -      -      -      -      -     vpermilps	$157, %xmm2, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm4, %xmm3, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm3, %xmm1, %xmm1
     -      -      -     0.96   0.04   0.98   0.02    -      -      -      -      -      -      -     vpermilps	$230, %xmm0, %xmm3
     -      -      -     0.02   0.98   0.93   0.07    -      -      -      -      -      -      -     vpermilps	$2, %xmm2, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm4, %xmm3, %xmm3
     -      -      -     0.98   0.02   0.54   0.46    -      -      -      -      -      -      -     vpermilps	$159, %xmm0, %xmm0
     -      -      -     0.05   0.95   0.52   0.48    -      -      -      -      -      -      -     vpermilps	$123, %xmm2, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm2, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm0, %xmm3, %xmm0
    0.50   0.50    -      -      -      -      -      -      -      -      -      -      -      -     movl	$-2147483648, %ecx
     -      -      -     0.07   0.93   0.07   0.93    -      -      -      -      -      -      -     vmovd	%ecx, %xmm2
     -      -      -     0.05   0.95   0.50   0.50    -      -      -      -      -      -      -     vxorps	%xmm2, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm0, %xmm1, %xmm0
     -      -      -      -      -      -     1.00    -      -     1.00   1.00    -      -      -     vmovaps	%xmm0, (%rdi)
    0.50   0.50    -      -      -      -      -     1.00    -      -      -      -      -      -     retq
    ```

For comparison, here is the assembly and analysis corresponding to semantically identical code from
[RTM](https://github.com/nfrechette/rtm).

```c++
rtm::quatf ab(rtm::quatf const& a, rtm::quatf const& b)
{
    return rtm::quat_mul(a, b);
}
```

??? tip "RTM LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      2000
    Total Cycles:      1313
    Total uOps:        2000

    Dispatch Width:    2
    uOps Per Cycle:    1.52
    IPC:               1.52
    Block RThroughput: 10.0


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      5     1.00    *                   vmovaps	(%rdi), %xmm0
     1      5     1.00    *                   vmovaps	(%rsi), %xmm1
     1      1     0.50                        vbroadcastss	%xmm1, %xmm2
     1      1     0.50                        vpermilps	$85, %xmm1, %xmm3
     1      1     0.50                        vpermilps	$170, %xmm1, %xmm4
     1      1     0.50                        vpermilps	$255, %xmm1, %xmm1
     1      2     1.00                        vmulps	%xmm1, %xmm0, %xmm1
     1      1     0.50                        vpermilps	$27, %xmm0, %xmm5
     1      2     1.00                        vmulps	%xmm2, %xmm5, %xmm2
     1      1     0.50                        vpermilpd	$1, %xmm0, %xmm5
     1      2     1.00                        vmulps	%xmm5, %xmm3, %xmm3
     1      6     1.00    *                   vxorps	.LCPI0_0(%rip), %xmm2, %xmm2
     1      3     1.00                        vaddps	%xmm2, %xmm1, %xmm1
     1      1     0.50                        vpermilps	$177, %xmm0, %xmm0
     1      2     1.00                        vmulps	%xmm0, %xmm4, %xmm0
     1      6     1.00    *                   vxorps	.LCPI0_1(%rip), %xmm3, %xmm2
     1      6     1.00    *                   vxorps	.LCPI0_2(%rip), %xmm0, %xmm0
     1      3     1.00                        vaddps	%xmm0, %xmm2, %xmm0
     1      3     1.00                        vaddps	%xmm0, %xmm1, %xmm0
     1      4     1.00                  U     retq


    Resources:
    [0]   - JALU0
    [1]   - JALU1
    [2]   - JDiv
    [3]   - JFPA
    [4]   - JFPM
    [5]   - JFPU0
    [6]   - JFPU1
    [7]   - JLAGU
    [8]   - JMul
    [9]   - JSAGU
    [10]  - JSTC
    [11]  - JVALU0
    [12]  - JVALU1
    [13]  - JVIMUL


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]
    0.50   0.50    -     10.01  8.99   10.01  8.99   6.00    -      -      -      -      -      -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
     -      -      -     0.01   0.99   0.01   0.99   1.00    -      -      -      -      -      -     vmovaps	(%rdi), %xmm0
     -      -      -     0.99   0.01   0.99   0.01   1.00    -      -      -      -      -      -     vmovaps	(%rsi), %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vbroadcastss	%xmm1, %xmm2
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vpermilps	$85, %xmm1, %xmm3
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vpermilps	$170, %xmm1, %xmm4
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vpermilps	$255, %xmm1, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm1, %xmm0, %xmm1
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vpermilps	$27, %xmm0, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm2, %xmm5, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vpermilpd	$1, %xmm0, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm5, %xmm3, %xmm3
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vxorps	.LCPI0_0(%rip), %xmm2, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm2, %xmm1, %xmm1
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vpermilps	$177, %xmm0, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm0, %xmm4, %xmm0
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vxorps	.LCPI0_1(%rip), %xmm3, %xmm2
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vxorps	.LCPI0_2(%rip), %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm0, %xmm2, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm0, %xmm1, %xmm0
    0.50   0.50    -      -      -      -      -     1.00    -      -      -      -      -      -     retq
    ```

Finally, for good measure, here is the same procedure and analysis for
[GLM](https://glm.g-truc.net/0.9.9/index.html)

```c++
glm::quat rotor_composition(glm::quat const& a, glm::quat const& b)
{
    return a * b;
}
```

??? tip "GLM LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      3900
    Total Cycles:      2314
    Total uOps:        3900

    Dispatch Width:    2
    uOps Per Cycle:    1.69
    IPC:               1.69
    Block RThroughput: 19.5


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      5     1.00    *                   vmovsd	(%rdi), %xmm1
     1      5     1.00    *                   vmovsd	8(%rdi), %xmm3
     1      1     0.50                        vmovshdup	%xmm1, %xmm8
     1      1     0.50                        vmovshdup	%xmm3, %xmm4
     1      5     1.00    *                   vmovss	(%rsi), %xmm5
     1      5     1.00    *                   vmovss	4(%rsi), %xmm6
     1      5     1.00    *                   vmovss	8(%rsi), %xmm7
     1      5     1.00    *                   vmovss	12(%rsi), %xmm2
     1      2     1.00                        vmulss	%xmm2, %xmm4, %xmm9
     1      2     1.00                        vmulss	%xmm5, %xmm1, %xmm0
     1      3     1.00                        vsubss	%xmm0, %xmm9, %xmm9
     1      2     1.00                        vmulss	%xmm6, %xmm8, %xmm0
     1      3     1.00                        vsubss	%xmm0, %xmm9, %xmm9
     1      2     1.00                        vmulss	%xmm7, %xmm3, %xmm0
     1      3     1.00                        vsubss	%xmm0, %xmm9, %xmm9
     1      2     1.00                        vmulss	%xmm5, %xmm4, %xmm10
     1      2     1.00                        vmulss	%xmm2, %xmm1, %xmm0
     1      3     1.00                        vaddss	%xmm0, %xmm10, %xmm10
     1      2     1.00                        vmulss	%xmm7, %xmm8, %xmm0
     1      3     1.00                        vaddss	%xmm10, %xmm0, %xmm10
     1      2     1.00                        vmulss	%xmm6, %xmm3, %xmm0
     1      3     1.00                        vsubss	%xmm0, %xmm10, %xmm10
     1      2     1.00                        vmulss	%xmm6, %xmm4, %xmm11
     1      2     1.00                        vmulss	%xmm2, %xmm8, %xmm0
     1      3     1.00                        vaddss	%xmm0, %xmm11, %xmm11
     1      2     1.00                        vmulss	%xmm5, %xmm3, %xmm0
     1      3     1.00                        vaddss	%xmm11, %xmm0, %xmm11
     1      2     1.00                        vmulss	%xmm7, %xmm1, %xmm0
     1      3     1.00                        vsubss	%xmm0, %xmm11, %xmm0
     1      1     0.50                        vinsertps	$16, %xmm0, %xmm10, %xmm0
     1      2     1.00                        vmulss	%xmm7, %xmm4, %xmm4
     1      2     1.00                        vmulss	%xmm2, %xmm3, %xmm2
     1      3     1.00                        vaddss	%xmm2, %xmm4, %xmm2
     1      2     1.00                        vmulss	%xmm6, %xmm1, %xmm1
     1      3     1.00                        vaddss	%xmm2, %xmm1, %xmm1
     1      2     1.00                        vmulss	%xmm5, %xmm8, %xmm2
     1      3     1.00                        vsubss	%xmm2, %xmm1, %xmm1
     1      1     0.50                        vinsertps	$16, %xmm9, %xmm1, %xmm1
     1      4     1.00                  U     retq


    Resources:
    [0]   - JALU0
    [1]   - JALU1
    [2]   - JDiv
    [3]   - JFPA
    [4]   - JFPM
    [5]   - JFPU0
    [6]   - JFPU1
    [7]   - JLAGU
    [8]   - JMul
    [9]   - JSAGU
    [10]  - JSTC
    [11]  - JVALU0
    [12]  - JVALU1
    [13]  - JVIMUL


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]
    0.50   0.50    -     16.98  21.02  16.98  21.02  7.00    -      -      -      -      -      -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
     -      -      -     0.99   0.01   0.99   0.01   1.00    -      -      -      -      -      -     vmovsd	(%rdi), %xmm1
     -      -      -     0.01   0.99   0.01   0.99   1.00    -      -      -      -      -      -     vmovsd	8(%rdi), %xmm3
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vmovshdup	%xmm1, %xmm8
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vmovshdup	%xmm3, %xmm4
     -      -      -     0.01   0.99   0.01   0.99   1.00    -      -      -      -      -      -     vmovss	(%rsi), %xmm5
     -      -      -     0.99   0.01   0.99   0.01   1.00    -      -      -      -      -      -     vmovss	4(%rsi), %xmm6
     -      -      -     0.98   0.02   0.98   0.02   1.00    -      -      -      -      -      -     vmovss	8(%rsi), %xmm7
     -      -      -     0.98   0.02   0.98   0.02   1.00    -      -      -      -      -      -     vmovss	12(%rsi), %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm2, %xmm4, %xmm9
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm5, %xmm1, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm0, %xmm9, %xmm9
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm8, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm0, %xmm9, %xmm9
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm7, %xmm3, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm0, %xmm9, %xmm9
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm5, %xmm4, %xmm10
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm2, %xmm1, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm0, %xmm10, %xmm10
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm7, %xmm8, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm10, %xmm0, %xmm10
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm3, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm0, %xmm10, %xmm10
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm4, %xmm11
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm2, %xmm8, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm0, %xmm11, %xmm11
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm5, %xmm3, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm11, %xmm0, %xmm11
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm7, %xmm1, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm0, %xmm11, %xmm0
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vinsertps	$16, %xmm0, %xmm10, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm7, %xmm4, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm2, %xmm3, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm2, %xmm4, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm1, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm2, %xmm1, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm5, %xmm8, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm2, %xmm1, %xmm1
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vinsertps	$16, %xmm9, %xmm1, %xmm1
    0.50   0.50    -      -      -      -      -     1.00    -      -      -      -      -      -     retq
    ```

## Motor-Point Application (Dual Quat Application)

```c++
kln::point motor_application(kln::motor const& m, kln::point const& p)
{
    return m(p);
}
```

??? tip "Klein LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      4900
    Total Cycles:      2518
    Total uOps:        5000

    Dispatch Width:    2
    uOps Per Cycle:    1.99
    IPC:               1.95
    Block RThroughput: 25.0


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      1     0.50                        movq	%rdi, %rax
     1      5     1.00    *                   vmovaps	(%rsi), %xmm0
     1      5     1.00    *                   vmovaps	16(%rsi), %xmm1
     1      1     0.50                        vbroadcastss	%xmm0, %xmm2
     1      1     0.50                        vpermilps	$156, %xmm0, %xmm3
     1      2     1.00                        vmulps	%xmm3, %xmm0, %xmm4
     1      1     0.50                        vpermilps	$120, %xmm0, %xmm5
     1      2     1.00                        vmulps	%xmm5, %xmm2, %xmm6
     1      3     1.00                        vsubps	%xmm6, %xmm4, %xmm4
     1      5     1.00    *                   vmovaps	.LCPI0_0(%rip), %xmm10
     1      2     1.00                        vmulps	%xmm10, %xmm4, %xmm8
     1      2     1.00                        vmulps	%xmm3, %xmm2, %xmm7
     1      2     1.00                        vmulps	%xmm5, %xmm0, %xmm4
     1      3     1.00                        vaddps	%xmm4, %xmm7, %xmm4
     1      2     1.00                        vmulps	%xmm10, %xmm4, %xmm9
     1      2     1.00                        vmulps	%xmm0, %xmm0, %xmm7
     1      1     0.50                        vpermilps	$1, %xmm7, %xmm4
     1      3     1.00                        vaddps	%xmm4, %xmm7, %xmm4
     1      1     0.50                        vpermilps	$158, %xmm7, %xmm6
     1      1     0.50                        vpermilps	$123, %xmm7, %xmm7
     1      3     1.00                        vaddps	%xmm7, %xmm6, %xmm6
     1      1     0.50                        movl	$-2147483648, %ecx
     2      8     0.50                        vmovd	%ecx, %xmm7
     1      1     0.50                        vxorps	%xmm7, %xmm6, %xmm6
     1      3     1.00                        vsubps	%xmm6, %xmm4, %xmm4
     1      1     0.50                        vpermilps	$156, %xmm1, %xmm6
     1      2     1.00                        vmulps	%xmm6, %xmm5, %xmm5
     1      2     1.00                        vmulps	%xmm1, %xmm2, %xmm2
     1      3     1.00                        vsubps	%xmm2, %xmm5, %xmm2
     1      1     0.50                        vpermilps	$120, %xmm1, %xmm5
     1      2     1.00                        vmulps	%xmm5, %xmm3, %xmm3
     1      3     1.00                        vsubps	%xmm3, %xmm2, %xmm2
     1      1     0.50                        vbroadcastss	%xmm1, %xmm1
     1      2     1.00                        vmulps	%xmm1, %xmm0, %xmm0
     1      3     1.00                        vsubps	%xmm0, %xmm2, %xmm0
     1      2     1.00                        vmulps	%xmm10, %xmm0, %xmm0
     1      5     1.00    *                   vmovaps	(%rdx), %xmm1
     1      1     0.50                        vpermilps	$156, %xmm1, %xmm2
     1      2     1.00                        vmulps	%xmm8, %xmm2, %xmm2
     1      1     0.50                        vpermilps	$120, %xmm1, %xmm3
     1      2     1.00                        vmulps	%xmm9, %xmm3, %xmm3
     1      3     1.00                        vaddps	%xmm3, %xmm2, %xmm2
     1      2     1.00                        vmulps	%xmm4, %xmm1, %xmm3
     1      3     1.00                        vaddps	%xmm3, %xmm2, %xmm2
     1      1     0.50                        vbroadcastss	%xmm1, %xmm1
     1      2     1.00                        vmulps	%xmm0, %xmm1, %xmm0
     1      3     1.00                        vaddps	%xmm2, %xmm0, %xmm0
     1      1     1.00           *            vmovaps	%xmm0, (%rdi)
     1      4     1.00                  U     retq


    Resources:
    [0]   - JALU0
    [1]   - JALU1
    [2]   - JDiv
    [3]   - JFPA
    [4]   - JFPM
    [5]   - JFPU0
    [6]   - JFPU1
    [7]   - JLAGU
    [8]   - JMul
    [9]   - JSAGU
    [10]  - JSTC
    [11]  - JVALU0
    [12]  - JVALU1
    [13]  - JVIMUL


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]
    1.50   1.50    -     22.01  22.99  22.97  23.03  5.00    -     1.00   1.00    -      -      -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
    0.50   0.50    -      -      -      -      -      -      -      -      -      -      -      -     movq	%rdi, %rax
     -      -      -     0.01   0.99   0.97   0.03   1.00    -      -      -      -      -      -     vmovaps	(%rsi), %xmm0
     -      -      -     0.97   0.03   0.02   0.98   1.00    -      -      -      -      -      -     vmovaps	16(%rsi), %xmm1
     -      -      -     0.02   0.98   0.02   0.98    -      -      -      -      -      -      -     vbroadcastss	%xmm0, %xmm2
     -      -      -     0.03   0.97   0.98   0.02    -      -      -      -      -      -      -     vpermilps	$156, %xmm0, %xmm3
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm3, %xmm0, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vpermilps	$120, %xmm0, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm5, %xmm2, %xmm6
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm6, %xmm4, %xmm4
     -      -      -     0.98   0.02   0.98   0.02   1.00    -      -      -      -      -      -     vmovaps	.LCPI0_0(%rip), %xmm10
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm10, %xmm4, %xmm8
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm3, %xmm2, %xmm7
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm5, %xmm0, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm4, %xmm7, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm10, %xmm4, %xmm9
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm0, %xmm0, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vpermilps	$1, %xmm7, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm4, %xmm7, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vpermilps	$158, %xmm7, %xmm6
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vpermilps	$123, %xmm7, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm7, %xmm6, %xmm6
    0.50   0.50    -      -      -      -      -      -      -      -      -      -      -      -     movl	$-2147483648, %ecx
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vmovd	%ecx, %xmm7
     -      -      -     0.02   0.98   1.00    -      -      -      -      -      -      -      -     vxorps	%xmm7, %xmm6, %xmm6
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm6, %xmm4, %xmm4
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vpermilps	$156, %xmm1, %xmm6
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm6, %xmm5, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm1, %xmm2, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm2, %xmm5, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vpermilps	$120, %xmm1, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm5, %xmm3, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm3, %xmm2, %xmm2
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vbroadcastss	%xmm1, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm1, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm0, %xmm2, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm10, %xmm0, %xmm0
     -      -      -     0.99   0.01   0.01   0.99   1.00    -      -      -      -      -      -     vmovaps	(%rdx), %xmm1
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vpermilps	$156, %xmm1, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm8, %xmm2, %xmm2
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vpermilps	$120, %xmm1, %xmm3
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm9, %xmm3, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm3, %xmm2, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm4, %xmm1, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm3, %xmm2, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vbroadcastss	%xmm1, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm0, %xmm1, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm2, %xmm0, %xmm0
     -      -      -      -      -      -     1.00    -      -     1.00   1.00    -      -      -     vmovaps	%xmm0, (%rdi)
    0.50   0.50    -      -      -      -      -     1.00    -      -      -      -      -      -     retq
    ```

```c++
glm::vec4 motor_application(glm::dualquat const& a, glm::vec4 const& b)
{
    return glm::mat3x4_cast(a) * b;
}
```

??? tip "GLM LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      10500
    Total Cycles:      9715
    Total uOps:        10500

    Dispatch Width:    2
    uOps Per Cycle:    1.08
    IPC:               1.08
    Block RThroughput: 71.0


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      5     1.00    *                   vmovss	(%rdi), %xmm9
     1      5     1.00    *                   vmovss	4(%rdi), %xmm1
     1      2     1.00                        vmulss	%xmm9, %xmm9, %xmm2
     1      2     1.00                        vmulss	%xmm1, %xmm1, %xmm3
     1      3     1.00                        vaddss	%xmm3, %xmm2, %xmm3
     1      5     1.00    *                   vmovss	8(%rdi), %xmm2
     1      2     1.00                        vmulss	%xmm2, %xmm2, %xmm4
     1      3     1.00                        vaddss	%xmm4, %xmm3, %xmm3
     1      5     1.00    *                   vmovss	12(%rdi), %xmm11
     1      2     1.00                        vmulss	%xmm11, %xmm11, %xmm4
     1      3     1.00                        vaddss	%xmm4, %xmm3, %xmm3
     1      1     0.50                        vinsertps	$16, %xmm1, %xmm11, %xmm4
     1      1     0.50                        vbroadcastss	%xmm3, %xmm3
     1      19    19.00                       vdivps	%xmm3, %xmm4, %xmm4
     1      1     0.50                        vinsertps	$16, %xmm2, %xmm9, %xmm6
     1      19    19.00                       vdivps	%xmm3, %xmm6, %xmm13
     1      3     1.00                        vaddps	%xmm4, %xmm4, %xmm3
     1      3     1.00                        vaddps	%xmm13, %xmm13, %xmm6
     1      2     1.00                        vmulss	%xmm6, %xmm1, %xmm5
     1      1     0.50                        vmovshdup	%xmm3, %xmm12
     1      2     1.00                        vmulss	%xmm3, %xmm2, %xmm7
     1      3     1.00                        vsubss	%xmm7, %xmm5, %xmm0
     1      2     1.00           *            vmovss	%xmm0, -4(%rsp)
     1      5     1.00    *                   vmovss	28(%rdi), %xmm14
     1      5     1.00    *                   vmovss	16(%rdi), %xmm15
     1      5     1.00    *                   vmovss	20(%rdi), %xmm8
     1      3     1.00                        vaddss	%xmm7, %xmm5, %xmm0
     1      2     1.00           *            vmovss	%xmm0, -12(%rsp)
     1      2     1.00                        vmulss	%xmm12, %xmm14, %xmm5
     1      1     0.50                        vmovshdup	%xmm6, %xmm7
     1      2     1.00                        vmulss	%xmm7, %xmm15, %xmm7
     1      3     1.00                        vsubss	%xmm7, %xmm5, %xmm5
     1      2     1.00                        vmulss	%xmm3, %xmm8, %xmm7
     1      3     1.00                        vsubss	%xmm7, %xmm5, %xmm5
     1      5     1.00    *                   vmovss	24(%rdi), %xmm7
     1      2     1.00                        vmulss	%xmm7, %xmm6, %xmm0
     1      3     1.00                        vaddss	%xmm5, %xmm0, %xmm0
     1      2     1.00           *            vmovss	%xmm0, -8(%rsp)
     1      2     1.00                        vmulss	%xmm4, %xmm11, %xmm0
     1      1     0.50                        vmovshdup	%xmm4, %xmm4
     1      2     1.00                        vmulss	%xmm4, %xmm1, %xmm4
     1      1     0.50                        vmovshdup	%xmm13, %xmm5
     1      2     1.00                        vmulss	%xmm5, %xmm2, %xmm5
     1      2     1.00                        vmulss	%xmm12, %xmm2, %xmm11
     1      2     1.00                        vmulss	%xmm6, %xmm2, %xmm2
     1      2     1.00                        vmulss	%xmm3, %xmm1, %xmm1
     1      3     1.00                        vaddss	%xmm1, %xmm2, %xmm12
     1      3     1.00                        vsubss	%xmm1, %xmm2, %xmm10
     1      2     1.00                        vmulss	%xmm13, %xmm9, %xmm2
     1      2     1.00                        vmulss	%xmm3, %xmm9, %xmm9
     1      3     1.00                        vsubss	%xmm9, %xmm11, %xmm13
     1      3     1.00                        vaddss	%xmm9, %xmm11, %xmm9
     1      3     1.00                        vaddss	%xmm2, %xmm0, %xmm1
     1      3     1.00                        vsubss	%xmm4, %xmm1, %xmm1
     1      3     1.00                        vsubss	%xmm5, %xmm1, %xmm11
     1      3     1.00                        vaddss	%xmm4, %xmm0, %xmm1
     1      3     1.00                        vsubss	%xmm2, %xmm1, %xmm1
     1      3     1.00                        vsubss	%xmm5, %xmm1, %xmm1
     1      3     1.00                        vaddss	%xmm5, %xmm0, %xmm0
     1      3     1.00                        vsubss	%xmm2, %xmm0, %xmm0
     1      3     1.00                        vsubss	%xmm4, %xmm0, %xmm2
     1      1     0.50                        vbroadcastss	%xmm14, %xmm0
     1      2     1.00                        vmulps	%xmm6, %xmm0, %xmm0
     1      1     0.50                        vbroadcastss	%xmm15, %xmm4
     1      2     1.00                        vmulps	%xmm3, %xmm4, %xmm4
     1      3     1.00                        vaddsubps	%xmm4, %xmm0, %xmm0
     1      1     0.50                        vbroadcastss	%xmm8, %xmm4
     1      1     0.50                        vpermilps	$225, %xmm6, %xmm5
     1      2     1.00                        vmulps	%xmm5, %xmm4, %xmm4
     1      3     1.00                        vaddps	%xmm4, %xmm0, %xmm5
     1      3     1.00                        vsubps	%xmm4, %xmm0, %xmm0
     1      1     0.50                        vblendps	$2, %xmm0, %xmm5, %xmm0
     1      1     0.50                        vpermilps	$225, %xmm3, %xmm3
     1      1     0.50                        vbroadcastss	%xmm7, %xmm4
     1      2     1.00                        vmulps	%xmm4, %xmm3, %xmm3
     1      3     1.00                        vsubps	%xmm3, %xmm0, %xmm3
     1      5     1.00    *                   vmovss	(%rsi), %xmm4
     1      5     1.00    *                   vmovss	4(%rsi), %xmm5
     1      2     1.00                        vmulss	%xmm11, %xmm4, %xmm0
     1      7     1.00    *                   vmulss	-12(%rsp), %xmm5, %xmm6
     1      3     1.00                        vaddss	%xmm0, %xmm6, %xmm0
     1      5     1.00    *                   vmovss	8(%rsi), %xmm6
     1      2     1.00                        vmulss	%xmm6, %xmm10, %xmm7
     1      3     1.00                        vaddss	%xmm0, %xmm7, %xmm0
     1      7     1.00    *                   vmulss	-4(%rsp), %xmm4, %xmm7
     1      2     1.00                        vmulss	%xmm1, %xmm5, %xmm1
     1      3     1.00                        vaddss	%xmm1, %xmm7, %xmm1
     1      2     1.00                        vmulss	%xmm6, %xmm9, %xmm7
     1      3     1.00                        vaddss	%xmm1, %xmm7, %xmm1
     1      1     0.50                        vinsertps	$16, %xmm1, %xmm0, %xmm0
     1      2     1.00                        vmulss	%xmm12, %xmm4, %xmm1
     1      2     1.00                        vmulss	%xmm13, %xmm5, %xmm7
     1      3     1.00                        vaddss	%xmm7, %xmm1, %xmm1
     1      2     1.00                        vmulss	%xmm2, %xmm6, %xmm2
     1      3     1.00                        vaddss	%xmm2, %xmm1, %xmm1
     1      7     1.00    *                   vmulss	-8(%rsp), %xmm5, %xmm2
     1      6     1.00    *                   vbroadcastss	.LCPI0_0(%rip), %xmm5
     1      1     0.50                        vxorps	%xmm5, %xmm2, %xmm2
     1      1     0.50                        vinsertps	$16, %xmm6, %xmm4, %xmm4
     1      2     1.00                        vmulps	%xmm3, %xmm4, %xmm3
     1      3     1.00                        vsubss	%xmm3, %xmm2, %xmm2
     1      1     0.50                        vmovshdup	%xmm3, %xmm3
     1      3     1.00                        vsubss	%xmm3, %xmm2, %xmm2
     1      1     0.50                        vinsertps	$16, %xmm2, %xmm1, %xmm1
     1      4     1.00                  U     retq


    Resources:
    [0]   - JALU0
    [1]   - JALU1
    [2]   - JDiv
    [3]   - JFPA
    [4]   - JFPM
    [5]   - JFPU0
    [6]   - JFPU1
    [7]   - JLAGU
    [8]   - JMul
    [9]   - JSAGU
    [10]  - JSTC
    [11]  - JVALU0
    [12]  - JVALU1
    [13]  - JVIMUL


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]
    0.50   0.50    -     51.00  86.00  50.00  54.00  16.00   -     3.00   3.00    -      -      -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmovss	(%rdi), %xmm9
     -      -      -     0.01   0.99   0.01   0.99   1.00    -      -      -      -      -      -     vmovss	4(%rdi), %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm9, %xmm9, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm1, %xmm1, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm3, %xmm2, %xmm3
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmovss	8(%rdi), %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm2, %xmm2, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm4, %xmm3, %xmm3
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vmovss	12(%rdi), %xmm11
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm11, %xmm11, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm4, %xmm3, %xmm3
     -      -      -     0.01   0.99   0.01   0.99    -      -      -      -      -      -      -     vinsertps	$16, %xmm1, %xmm11, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vbroadcastss	%xmm3, %xmm3
     -      -      -      -     19.00   -     1.00    -      -      -      -      -      -      -     vdivps	%xmm3, %xmm4, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vinsertps	$16, %xmm2, %xmm9, %xmm6
     -      -      -      -     19.00   -     1.00    -      -      -      -      -      -      -     vdivps	%xmm3, %xmm6, %xmm13
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm4, %xmm4, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm13, %xmm13, %xmm6
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm1, %xmm5
     -      -      -     1.00    -      -     1.00    -      -      -      -      -      -      -     vmovshdup	%xmm3, %xmm12
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm3, %xmm2, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm7, %xmm5, %xmm0
     -      -      -      -      -      -     1.00    -      -     1.00   1.00    -      -      -     vmovss	%xmm0, -4(%rsp)
     -      -      -     0.99   0.01   0.99   0.01   1.00    -      -      -      -      -      -     vmovss	28(%rdi), %xmm14
     -      -      -     0.99   0.01   0.99   0.01   1.00    -      -      -      -      -      -     vmovss	16(%rdi), %xmm15
     -      -      -     0.01   0.99   0.01   0.99   1.00    -      -      -      -      -      -     vmovss	20(%rdi), %xmm8
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm7, %xmm5, %xmm0
     -      -      -      -      -      -     1.00    -      -     1.00   1.00    -      -      -     vmovss	%xmm0, -12(%rsp)
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm12, %xmm14, %xmm5
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vmovshdup	%xmm6, %xmm7
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm7, %xmm15, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm7, %xmm5, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm3, %xmm8, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm7, %xmm5, %xmm5
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vmovss	24(%rdi), %xmm7
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm7, %xmm6, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm5, %xmm0, %xmm0
     -      -      -      -      -      -     1.00    -      -     1.00   1.00    -      -      -     vmovss	%xmm0, -8(%rsp)
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm4, %xmm11, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vmovshdup	%xmm4, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm4, %xmm1, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vmovshdup	%xmm13, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm5, %xmm2, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm12, %xmm2, %xmm11
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm2, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm3, %xmm1, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm1, %xmm2, %xmm12
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm1, %xmm2, %xmm10
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm13, %xmm9, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm3, %xmm9, %xmm9
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm9, %xmm11, %xmm13
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm9, %xmm11, %xmm9
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm2, %xmm0, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm4, %xmm1, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm5, %xmm1, %xmm11
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm4, %xmm0, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm2, %xmm1, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm5, %xmm1, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm5, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm2, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm4, %xmm0, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vbroadcastss	%xmm14, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm6, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vbroadcastss	%xmm15, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm3, %xmm4, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddsubps	%xmm4, %xmm0, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vbroadcastss	%xmm8, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vpermilps	$225, %xmm6, %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm5, %xmm4, %xmm4
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddps	%xmm4, %xmm0, %xmm5
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm4, %xmm0, %xmm0
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vblendps	$2, %xmm0, %xmm5, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vpermilps	$225, %xmm3, %xmm3
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vbroadcastss	%xmm7, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm4, %xmm3, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubps	%xmm3, %xmm0, %xmm3
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmovss	(%rsi), %xmm4
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmovss	4(%rsi), %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm11, %xmm4, %xmm0
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmulss	-12(%rsp), %xmm5, %xmm6
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm0, %xmm6, %xmm0
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vmovss	8(%rsi), %xmm6
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm10, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm0, %xmm7, %xmm0
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmulss	-4(%rsp), %xmm4, %xmm7
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm1, %xmm5, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm1, %xmm7, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm6, %xmm9, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm1, %xmm7, %xmm1
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vinsertps	$16, %xmm1, %xmm0, %xmm0
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm12, %xmm4, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm13, %xmm5, %xmm7
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm7, %xmm1, %xmm1
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulss	%xmm2, %xmm6, %xmm2
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vaddss	%xmm2, %xmm1, %xmm1
     -      -      -      -     1.00    -     1.00   1.00    -      -      -      -      -      -     vmulss	-8(%rsp), %xmm5, %xmm2
     -      -      -     1.00    -     1.00    -     1.00    -      -      -      -      -      -     vbroadcastss	.LCPI0_0(%rip), %xmm5
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vxorps	%xmm5, %xmm2, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vinsertps	$16, %xmm6, %xmm4, %xmm4
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vmulps	%xmm3, %xmm4, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm3, %xmm2, %xmm2
     -      -      -     0.99   0.01   0.99   0.01    -      -      -      -      -      -      -     vmovshdup	%xmm3, %xmm3
     -      -      -     1.00    -     1.00    -      -      -      -      -      -      -      -     vsubss	%xmm3, %xmm2, %xmm2
     -      -      -      -     1.00    -     1.00    -      -      -      -      -      -      -     vinsertps	$16, %xmm2, %xmm1, %xmm1
    0.50   0.50    -      -      -      -      -     1.00    -      -      -      -      -      -     retq
    ```

!!! note

    An RTM implementation of the dual-quat application is not provided (internally, RTM uses a type called `qvvf` which stores scale, translation, and rotation as separate components). The `qvvf` cannot be interpolated the same way as a motor or dual quaternion so it is omitted from this portion of the analysis.
