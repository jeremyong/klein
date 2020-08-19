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
    Instructions:      2400
    Total Cycles:      821
    Total uOps:        2400

    Dispatch Width:    6
    uOps Per Cycle:    2.92
    IPC:               2.92
    Block RThroughput: 8.0


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      6     0.50    *                   movaps	(%rdi), %xmm0
     1      6     0.50    *                   movaps	(%rsi), %xmm1
     1      1     0.33                        movaps	%xmm0, %xmm2
     1      1     1.00                        shufps	$0, %xmm0, %xmm2
     1      4     0.50                        mulps	%xmm1, %xmm2
     1      1     0.33                        movaps	%xmm0, %xmm3
     1      1     1.00                        shufps	$121, %xmm0, %xmm3
     1      1     0.33                        movaps	%xmm1, %xmm4
     1      1     1.00                        shufps	$157, %xmm1, %xmm4
     1      4     0.50                        mulps	%xmm3, %xmm4
     1      4     0.50                        subps	%xmm4, %xmm2
     1      1     0.33                        movaps	%xmm0, %xmm3
     1      1     1.00                        shufps	$230, %xmm0, %xmm3
     1      1     0.33                        movaps	%xmm1, %xmm4
     1      1     1.00                        shufps	$2, %xmm1, %xmm4
     1      4     0.50                        mulps	%xmm3, %xmm4
     1      1     1.00                        shufps	$159, %xmm0, %xmm0
     1      1     1.00                        shufps	$123, %xmm1, %xmm1
     1      4     0.50                        mulps	%xmm0, %xmm1
     1      4     0.50                        addps	%xmm4, %xmm1
     1      1     0.25                        movl	$-2147483648, %eax
     1      1     1.00                        movd	%eax, %xmm0
     1      1     0.33                        pxor	%xmm1, %xmm0
     1      4     0.50                        addps	%xmm2, %xmm0


    Resources:
    [0]   - SKLDivider
    [1]   - SKLFPDivider
    [2]   - SKLPort0
    [3]   - SKLPort1
    [4]   - SKLPort2
    [5]   - SKLPort3
    [6]   - SKLPort4
    [7]   - SKLPort5
    [8]   - SKLPort6
    [9]   - SKLPort7


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]
     -      -     6.49   6.50   1.00   1.00    -     8.01   1.00    -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    Instructions:
     -      -      -      -      -     1.00    -      -      -      -     movaps	(%rdi), %xmm0
     -      -      -      -     1.00    -      -      -      -      -     movaps	(%rsi), %xmm1
     -      -     0.50   0.50    -      -      -      -      -      -     movaps	%xmm0, %xmm2
     -      -      -      -      -      -      -     1.00    -      -     shufps	$0, %xmm0, %xmm2
     -      -     0.03   0.97    -      -      -      -      -      -     mulps	%xmm1, %xmm2
     -      -     0.50   0.50    -      -      -      -      -      -     movaps	%xmm0, %xmm3
     -      -      -      -      -      -      -     1.00    -      -     shufps	$121, %xmm0, %xmm3
     -      -     0.51   0.48    -      -      -     0.01    -      -     movaps	%xmm1, %xmm4
     -      -      -      -      -      -      -     1.00    -      -     shufps	$157, %xmm1, %xmm4
     -      -     0.98   0.02    -      -      -      -      -      -     mulps	%xmm3, %xmm4
     -      -     0.94   0.06    -      -      -      -      -      -     subps	%xmm4, %xmm2
     -      -     0.50   0.50    -      -      -      -      -      -     movaps	%xmm0, %xmm3
     -      -      -      -      -      -      -     1.00    -      -     shufps	$230, %xmm0, %xmm3
     -      -     0.50   0.50    -      -      -      -      -      -     movaps	%xmm1, %xmm4
     -      -      -      -      -      -      -     1.00    -      -     shufps	$2, %xmm1, %xmm4
     -      -     0.51   0.49    -      -      -      -      -      -     mulps	%xmm3, %xmm4
     -      -      -      -      -      -      -     1.00    -      -     shufps	$159, %xmm0, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     shufps	$123, %xmm1, %xmm1
     -      -     0.53   0.47    -      -      -      -      -      -     mulps	%xmm0, %xmm1
     -      -     0.02   0.98    -      -      -      -      -      -     addps	%xmm4, %xmm1
     -      -      -      -      -      -      -      -     1.00    -     movl	$-2147483648, %eax
     -      -      -      -      -      -      -     1.00    -      -     movd	%eax, %xmm0
     -      -     0.48   0.52    -      -      -      -      -      -     pxor	%xmm1, %xmm0
     -      -     0.49   0.51    -      -      -      -      -      -     addps	%xmm2, %xmm0
    ```

For comparison, here is the assembly and analysis corresponding to semantically identical code from
[RTM](https://github.com/nfrechette/rtm).

```c++
rtm::quatf ab(rtm::quatf const& a, rtm::quatf const& b)
{
    return rtm::quat_mul(a, b);
}
```

??? note "RTM LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      2300
    Total Cycles:      824
    Total uOps:        2600

    Dispatch Width:    6
    uOps Per Cycle:    3.16
    IPC:               2.79
    Block RThroughput: 7.0


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      6     0.50    *                   movaps	(%rdi), %xmm0
     1      6     0.50    *                   movaps	(%rsi), %xmm2
     1      1     0.33                        movaps	%xmm2, %xmm1
     1      1     1.00                        shufps	$0, %xmm2, %xmm1
     1      1     0.33                        movaps	%xmm2, %xmm3
     1      1     1.00                        shufps	$85, %xmm2, %xmm3
     1      1     0.33                        movaps	%xmm2, %xmm4
     1      1     1.00                        shufps	$170, %xmm2, %xmm4
     1      1     1.00                        shufps	$255, %xmm2, %xmm2
     1      4     0.50                        mulps	%xmm0, %xmm2
     1      1     0.33                        movaps	%xmm0, %xmm5
     1      1     1.00                        shufps	$27, %xmm0, %xmm5
     1      4     0.50                        mulps	%xmm5, %xmm1
     1      1     1.00                        shufps	$177, %xmm5, %xmm5
     1      4     0.50                        mulps	%xmm3, %xmm5
     2      7     0.50    *                   xorps	.LCPI0_0(%rip), %xmm1
     1      1     1.00                        shufps	$177, %xmm0, %xmm0
     1      4     0.50                        mulps	%xmm4, %xmm0
     2      7     0.50    *                   xorps	.LCPI0_1(%rip), %xmm5
     2      7     0.50    *                   xorps	.LCPI0_2(%rip), %xmm0
     1      4     0.50                        addps	%xmm2, %xmm1
     1      4     0.50                        addps	%xmm5, %xmm0
     1      4     0.50                        addps	%xmm1, %xmm0


    Resources:
    [0]   - SKLDivider
    [1]   - SKLFPDivider
    [2]   - SKLPort0
    [3]   - SKLPort1
    [4]   - SKLPort2
    [5]   - SKLPort3
    [6]   - SKLPort4
    [7]   - SKLPort5
    [8]   - SKLPort6
    [9]   - SKLPort7


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]
     -      -     6.49   6.50   2.50   2.50    -     8.01    -      -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    Instructions:
     -      -      -      -     0.50   0.50    -      -      -      -     movaps	(%rdi), %xmm0
     -      -      -      -     0.49   0.51    -      -      -      -     movaps	(%rsi), %xmm2
     -      -     0.03   0.96    -      -      -     0.01    -      -     movaps	%xmm2, %xmm1
     -      -      -      -      -      -      -     1.00    -      -     shufps	$0, %xmm2, %xmm1
     -      -     0.95   0.05    -      -      -      -      -      -     movaps	%xmm2, %xmm3
     -      -      -      -      -      -      -     1.00    -      -     shufps	$85, %xmm2, %xmm3
     -      -     0.04   0.96    -      -      -      -      -      -     movaps	%xmm2, %xmm4
     -      -      -      -      -      -      -     1.00    -      -     shufps	$170, %xmm2, %xmm4
     -      -      -      -      -      -      -     1.00    -      -     shufps	$255, %xmm2, %xmm2
     -      -     0.49   0.51    -      -      -      -      -      -     mulps	%xmm0, %xmm2
     -      -     0.95   0.05    -      -      -      -      -      -     movaps	%xmm0, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     shufps	$27, %xmm0, %xmm5
     -      -     0.52   0.48    -      -      -      -      -      -     mulps	%xmm5, %xmm1
     -      -      -      -      -      -      -     1.00    -      -     shufps	$177, %xmm5, %xmm5
     -      -     0.49   0.51    -      -      -      -      -      -     mulps	%xmm3, %xmm5
     -      -     0.48   0.52   0.50   0.50    -      -      -      -     xorps	.LCPI0_0(%rip), %xmm1
     -      -      -      -      -      -      -     1.00    -      -     shufps	$177, %xmm0, %xmm0
     -      -     0.52   0.48    -      -      -      -      -      -     mulps	%xmm4, %xmm0
     -      -     0.48   0.52   0.50   0.50    -      -      -      -     xorps	.LCPI0_1(%rip), %xmm5
     -      -      -      -     0.51   0.49    -     1.00    -      -     xorps	.LCPI0_2(%rip), %xmm0
     -      -     0.51   0.49    -      -      -      -      -      -     addps	%xmm2, %xmm1
     -      -     0.52   0.48    -      -      -      -      -      -     addps	%xmm5, %xmm0
     -      -     0.51   0.49    -      -      -      -      -      -     addps	%xmm1, %xmm0
    ```

Finally, for good measure, here is the same procedure and analysis for
[GLM](https://glm.g-truc.net/0.9.9/index.html)

```c++
glm::quat rotor_composition(glm::quat const& a, glm::quat const& b)
{
    return a * b;
}
```

??? note "GLM LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      5700
    Total Cycles:      1522
    Total uOps:        5800

    Dispatch Width:    6
    uOps Per Cycle:    3.81
    IPC:               3.75
    Block RThroughput: 14.0


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      5     0.50    *                   movss	(%rdi), %xmm4
     1      5     0.50    *                   movss	4(%rdi), %xmm3
     1      5     0.50    *                   movss	8(%rdi), %xmm2
     1      5     0.50    *                   movss	12(%rdi), %xmm0
     1      5     0.50    *                   movss	(%rsi), %xmm9
     1      5     0.50    *                   movss	4(%rsi), %xmm8
     1      5     0.50    *                   movss	8(%rsi), %xmm7
     1      5     0.50    *                   movss	12(%rsi), %xmm10
     1      1     0.33                        movaps	%xmm0, %xmm5
     1      1     0.33                        movaps	%xmm4, %xmm1
     1      1     0.33                        movaps	%xmm0, %xmm6
     1      4     0.50                        mulss	%xmm10, %xmm1
     1      1     0.33                        movaps	%xmm2, %xmm11
     1      4     0.50                        mulss	%xmm9, %xmm5
     1      4     0.50                        mulss	%xmm8, %xmm6
     1      4     0.50                        mulss	%xmm10, %xmm11
     1      4     0.50                        addss	%xmm1, %xmm5
     1      1     0.33                        movaps	%xmm3, %xmm1
     1      4     0.50                        mulss	%xmm7, %xmm1
     1      4     0.50                        addss	%xmm1, %xmm5
     1      1     0.33                        movaps	%xmm2, %xmm1
     1      4     0.50                        mulss	%xmm8, %xmm1
     1      4     0.50                        subss	%xmm1, %xmm5
     1      1     0.33                        movaps	%xmm3, %xmm1
     1      4     0.50                        mulss	%xmm10, %xmm1
     1      4     0.50                        addss	%xmm1, %xmm6
     1      1     0.33                        movaps	%xmm2, %xmm1
     1      4     0.50                        mulss	%xmm9, %xmm1
     1      4     0.50                        mulss	%xmm7, %xmm2
     1      4     0.50                        addss	%xmm1, %xmm6
     1      1     0.33                        movaps	%xmm4, %xmm1
     1      4     0.50                        mulss	%xmm7, %xmm1
     1      4     0.50                        subss	%xmm1, %xmm6
     1      1     0.33                        movaps	%xmm0, %xmm1
     1      4     0.50                        mulss	%xmm7, %xmm1
     1      4     0.50                        mulss	%xmm10, %xmm0
     1      1     1.00                        unpcklps	%xmm6, %xmm5
     1      1     0.33                        movaps	%xmm5, %xmm7
     1      4     0.50                        addss	%xmm11, %xmm1
     1      1     0.33                        movaps	%xmm4, %xmm11
     1      4     0.50                        mulss	%xmm8, %xmm11
     1      4     0.50                        mulss	%xmm9, %xmm4
     1      4     0.50                        addss	%xmm11, %xmm1
     1      1     0.33                        movaps	%xmm3, %xmm11
     1      4     0.50                        mulss	%xmm8, %xmm3
     1      4     0.50                        subss	%xmm4, %xmm0
     1      4     0.50                        mulss	%xmm9, %xmm11
     1      4     0.50                        subss	%xmm3, %xmm0
     1      4     0.50                        subss	%xmm11, %xmm1
     1      4     0.50                        subss	%xmm2, %xmm0
     1      1     1.00                        unpcklps	%xmm0, %xmm1
     1      1     1.00                        movlhps	%xmm1, %xmm7
     2      1     1.00           *            movaps	%xmm7, -40(%rsp)
     1      5     0.50    *                   movq	-32(%rsp), %rax
     1      5     0.50    *                   movq	-40(%rsp), %xmm0
     1      1     1.00                        movq	%rax, %xmm1
     1      1     1.00           *            movq	%rax, -16(%rsp)


    Resources:
    [0]   - SKLDivider
    [1]   - SKLFPDivider
    [2]   - SKLPort0
    [3]   - SKLPort1
    [4]   - SKLPort2
    [5]   - SKLPort3
    [6]   - SKLPort4
    [7]   - SKLPort5
    [8]   - SKLPort6
    [9]   - SKLPort7


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]
     -      -     15.00  15.00  5.01   5.01   2.00   15.00   -     1.98

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    Instructions:
     -      -      -      -      -     1.00    -      -      -      -     movss	(%rdi), %xmm4
     -      -      -      -     1.00    -      -      -      -      -     movss	4(%rdi), %xmm3
     -      -      -      -     0.01   0.99    -      -      -      -     movss	8(%rdi), %xmm2
     -      -      -      -     0.99   0.01    -      -      -      -     movss	12(%rdi), %xmm0
     -      -      -      -      -     1.00    -      -      -      -     movss	(%rsi), %xmm9
     -      -      -      -     1.00    -      -      -      -      -     movss	4(%rsi), %xmm8
     -      -      -      -     0.98   0.02    -      -      -      -     movss	8(%rsi), %xmm7
     -      -      -      -     0.02   0.98    -      -      -      -     movss	12(%rsi), %xmm10
     -      -     0.48    -      -      -      -     0.52    -      -     movaps	%xmm0, %xmm5
     -      -      -     0.49    -      -      -     0.51    -      -     movaps	%xmm4, %xmm1
     -      -     0.98   0.01    -      -      -     0.01    -      -     movaps	%xmm0, %xmm6
     -      -     0.98   0.02    -      -      -      -      -      -     mulss	%xmm10, %xmm1
     -      -     0.01   0.01    -      -      -     0.98    -      -     movaps	%xmm2, %xmm11
     -      -     0.50   0.50    -      -      -      -      -      -     mulss	%xmm9, %xmm5
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm8, %xmm6
     -      -     0.50   0.50    -      -      -      -      -      -     mulss	%xmm10, %xmm11
     -      -     0.49   0.51    -      -      -      -      -      -     addss	%xmm1, %xmm5
     -      -      -     0.01    -      -      -     0.99    -      -     movaps	%xmm3, %xmm1
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm7, %xmm1
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm1, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm2, %xmm1
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm8, %xmm1
     -      -     0.01   0.99    -      -      -      -      -      -     subss	%xmm1, %xmm5
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm3, %xmm1
     -      -     0.50   0.50    -      -      -      -      -      -     mulss	%xmm10, %xmm1
     -      -     0.49   0.51    -      -      -      -      -      -     addss	%xmm1, %xmm6
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm2, %xmm1
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm9, %xmm1
     -      -     0.01   0.99    -      -      -      -      -      -     mulss	%xmm7, %xmm2
     -      -     0.50   0.50    -      -      -      -      -      -     addss	%xmm1, %xmm6
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm4, %xmm1
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm7, %xmm1
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm1, %xmm6
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm0, %xmm1
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm7, %xmm1
     -      -     0.50   0.50    -      -      -      -      -      -     mulss	%xmm10, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     unpcklps	%xmm6, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm5, %xmm7
     -      -     0.50   0.50    -      -      -      -      -      -     addss	%xmm11, %xmm1
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm4, %xmm11
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm8, %xmm11
     -      -     0.02   0.98    -      -      -      -      -      -     mulss	%xmm9, %xmm4
     -      -     0.02   0.98    -      -      -      -      -      -     addss	%xmm11, %xmm1
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm3, %xmm11
     -      -     0.98   0.02    -      -      -      -      -      -     mulss	%xmm8, %xmm3
     -      -     0.01   0.99    -      -      -      -      -      -     subss	%xmm4, %xmm0
     -      -     0.51   0.49    -      -      -      -      -      -     mulss	%xmm9, %xmm11
     -      -     0.02   0.98    -      -      -      -      -      -     subss	%xmm3, %xmm0
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm11, %xmm1
     -      -     0.01   0.99    -      -      -      -      -      -     subss	%xmm2, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     unpcklps	%xmm0, %xmm1
     -      -      -      -      -      -      -     1.00    -      -     movlhps	%xmm1, %xmm7
     -      -      -      -     0.01    -     1.00    -      -     0.99   movaps	%xmm7, -40(%rsp)
     -      -      -      -      -     1.00    -      -      -      -     movq	-32(%rsp), %rax
     -      -      -      -     1.00    -      -      -      -      -     movq	-40(%rsp), %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movq	%rax, %xmm1
     -      -      -      -      -     0.01   1.00    -      -     0.99   movq	%rax, -16(%rsp)
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
    Instructions:      5900
    Total Cycles:      1831
    Total uOps:        5900

    Dispatch Width:    6
    uOps Per Cycle:    3.22
    IPC:               3.22
    Block RThroughput: 13.5


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      6     0.50    *                   movaps	(%rdi), %xmm3
     1      6     0.50    *                   movaps	16(%rdi), %xmm6
     1      1     0.33                        movaps	%xmm3, %xmm12
     1      1     1.00                        shufps	$0, %xmm3, %xmm12
     1      1     0.33                        movaps	%xmm3, %xmm11
     1      1     0.33                        movaps	%xmm3, %xmm10
     1      1     0.33                        movaps	%xmm12, %xmm8
     1      1     0.33                        movaps	%xmm12, %xmm9
     1      1     0.33                        movaps	%xmm3, %xmm4
     1      1     0.33                        movaps	%xmm3, %xmm1
     1      1     0.33                        movaps	%xmm6, %xmm7
     1      4     0.50                        mulps	%xmm6, %xmm12
     1      1     0.33                        movaps	%xmm6, %xmm0
     1      1     1.00                        shufps	$0, %xmm6, %xmm6
     1      4     0.50                        mulps	%xmm3, %xmm6
     1      1     1.00                        shufps	$156, %xmm3, %xmm3
     1      4     0.50                        mulps	%xmm3, %xmm11
     1      1     1.00                        shufps	$120, %xmm10, %xmm10
     1      4     0.50                        mulps	%xmm10, %xmm8
     1      4     0.50                        subps	%xmm8, %xmm11
     1      4     0.50                        mulps	%xmm3, %xmm9
     1      4     0.50                        mulps	%xmm10, %xmm4
     1      4     0.50                        addps	%xmm9, %xmm4
     1      4     0.50                        mulps	%xmm1, %xmm1
     1      1     0.33                        movaps	%xmm1, %xmm5
     1      1     1.00                        shufps	$1, %xmm1, %xmm5
     1      4     0.50                        addps	%xmm1, %xmm5
     1      1     0.33                        movaps	%xmm1, %xmm2
     1      1     1.00                        shufps	$158, %xmm1, %xmm2
     1      1     1.00                        shufps	$123, %xmm1, %xmm1
     1      4     0.50                        addps	%xmm2, %xmm1
     1      1     0.25                        movl	$-2147483648, %eax
     1      1     1.00                        movd	%eax, %xmm2
     1      1     0.33                        pxor	%xmm1, %xmm2
     1      6     0.50    *                   movaps	.LCPI3_0(%rip), %xmm1
     1      4     0.50                        mulps	%xmm1, %xmm11
     1      4     0.50                        mulps	%xmm1, %xmm4
     1      4     0.50                        subps	%xmm2, %xmm5
     1      1     1.00                        shufps	$156, %xmm7, %xmm7
     1      4     0.50                        mulps	%xmm10, %xmm7
     1      4     0.50                        subps	%xmm12, %xmm7
     1      1     1.00                        shufps	$120, %xmm0, %xmm0
     1      4     0.50                        mulps	%xmm3, %xmm0
     1      4     0.50                        subps	%xmm0, %xmm7
     1      4     0.50                        subps	%xmm6, %xmm7
     1      4     0.50                        mulps	%xmm1, %xmm7
     1      6     0.50    *                   movaps	(%rsi), %xmm0
     1      1     0.33                        movaps	%xmm0, %xmm1
     1      1     1.00                        shufps	$156, %xmm0, %xmm1
     1      4     0.50                        mulps	%xmm11, %xmm1
     1      1     0.33                        movaps	%xmm0, %xmm2
     1      1     1.00                        shufps	$120, %xmm0, %xmm2
     1      4     0.50                        mulps	%xmm4, %xmm2
     1      4     0.50                        addps	%xmm1, %xmm2
     1      4     0.50                        mulps	%xmm0, %xmm5
     1      4     0.50                        addps	%xmm2, %xmm5
     1      1     1.00                        shufps	$0, %xmm0, %xmm0
     1      4     0.50                        mulps	%xmm7, %xmm0
     1      4     0.50                        addps	%xmm5, %xmm0


    Resources:
    [0]   - SKLDivider
    [1]   - SKLFPDivider
    [2]   - SKLPort0
    [3]   - SKLPort1
    [4]   - SKLPort2
    [5]   - SKLPort3
    [6]   - SKLPort4
    [7]   - SKLPort5
    [8]   - SKLPort6
    [9]   - SKLPort7


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]
     -      -     18.01  18.01  2.00   2.00    -     17.98  1.00    -

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    Instructions:
     -      -      -      -      -     1.00    -      -      -      -     movaps	(%rdi), %xmm3
     -      -      -      -     1.00    -      -      -      -      -     movaps	16(%rdi), %xmm6
     -      -     0.01   0.98    -      -      -     0.01    -      -     movaps	%xmm3, %xmm12
     -      -      -      -      -      -      -     1.00    -      -     shufps	$0, %xmm3, %xmm12
     -      -      -     1.00    -      -      -      -      -      -     movaps	%xmm3, %xmm11
     -      -     0.01   0.49    -      -      -     0.50    -      -     movaps	%xmm3, %xmm10
     -      -     0.49   0.01    -      -      -     0.50    -      -     movaps	%xmm12, %xmm8
     -      -      -     0.50    -      -      -     0.50    -      -     movaps	%xmm12, %xmm9
     -      -      -     0.51    -      -      -     0.49    -      -     movaps	%xmm3, %xmm4
     -      -     0.50   0.01    -      -      -     0.49    -      -     movaps	%xmm3, %xmm1
     -      -     0.01   0.50    -      -      -     0.49    -      -     movaps	%xmm6, %xmm7
     -      -      -     1.00    -      -      -      -      -      -     mulps	%xmm6, %xmm12
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm6, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     shufps	$0, %xmm6, %xmm6
     -      -     0.50   0.50    -      -      -      -      -      -     mulps	%xmm3, %xmm6
     -      -      -      -      -      -      -     1.00    -      -     shufps	$156, %xmm3, %xmm3
     -      -     0.98   0.02    -      -      -      -      -      -     mulps	%xmm3, %xmm11
     -      -      -      -      -      -      -     1.00    -      -     shufps	$120, %xmm10, %xmm10
     -      -     0.02   0.98    -      -      -      -      -      -     mulps	%xmm10, %xmm8
     -      -     0.03   0.97    -      -      -      -      -      -     subps	%xmm8, %xmm11
     -      -     0.01   0.99    -      -      -      -      -      -     mulps	%xmm3, %xmm9
     -      -     0.49   0.51    -      -      -      -      -      -     mulps	%xmm10, %xmm4
     -      -     0.49   0.51    -      -      -      -      -      -     addps	%xmm9, %xmm4
     -      -     0.51   0.49    -      -      -      -      -      -     mulps	%xmm1, %xmm1
     -      -     0.49    -      -      -      -     0.51    -      -     movaps	%xmm1, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     shufps	$1, %xmm1, %xmm5
     -      -     0.99   0.01    -      -      -      -      -      -     addps	%xmm1, %xmm5
     -      -     0.01   0.50    -      -      -     0.49    -      -     movaps	%xmm1, %xmm2
     -      -      -      -      -      -      -     1.00    -      -     shufps	$158, %xmm1, %xmm2
     -      -      -      -      -      -      -     1.00    -      -     shufps	$123, %xmm1, %xmm1
     -      -     0.03   0.97    -      -      -      -      -      -     addps	%xmm2, %xmm1
     -      -      -      -      -      -      -      -     1.00    -     movl	$-2147483648, %eax
     -      -      -      -      -      -      -     1.00    -      -     movd	%eax, %xmm2
     -      -     0.99   0.01    -      -      -      -      -      -     pxor	%xmm1, %xmm2
     -      -      -      -      -     1.00    -      -      -      -     movaps	.LCPI3_0(%rip), %xmm1
     -      -     0.52   0.48    -      -      -      -      -      -     mulps	%xmm1, %xmm11
     -      -     0.01   0.99    -      -      -      -      -      -     mulps	%xmm1, %xmm4
     -      -     0.98   0.02    -      -      -      -      -      -     subps	%xmm2, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     shufps	$156, %xmm7, %xmm7
     -      -     0.49   0.51    -      -      -      -      -      -     mulps	%xmm10, %xmm7
     -      -     0.50   0.50    -      -      -      -      -      -     subps	%xmm12, %xmm7
     -      -      -      -      -      -      -     1.00    -      -     shufps	$120, %xmm0, %xmm0
     -      -     0.52   0.48    -      -      -      -      -      -     mulps	%xmm3, %xmm0
     -      -     0.50   0.50    -      -      -      -      -      -     subps	%xmm0, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     subps	%xmm6, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     mulps	%xmm1, %xmm7
     -      -      -      -     1.00    -      -      -      -      -     movaps	(%rsi), %xmm0
     -      -     0.48   0.52    -      -      -      -      -      -     movaps	%xmm0, %xmm1
     -      -      -      -      -      -      -     1.00    -      -     shufps	$156, %xmm0, %xmm1
     -      -     0.99   0.01    -      -      -      -      -      -     mulps	%xmm11, %xmm1
     -      -      -     1.00    -      -      -      -      -      -     movaps	%xmm0, %xmm2
     -      -      -      -      -      -      -     1.00    -      -     shufps	$120, %xmm0, %xmm2
     -      -     0.50   0.50    -      -      -      -      -      -     mulps	%xmm4, %xmm2
     -      -     0.99   0.01    -      -      -      -      -      -     addps	%xmm1, %xmm2
     -      -     0.01   0.99    -      -      -      -      -      -     mulps	%xmm0, %xmm5
     -      -     0.99   0.01    -      -      -      -      -      -     addps	%xmm2, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     shufps	$0, %xmm0, %xmm0
     -      -     0.98   0.02    -      -      -      -      -      -     mulps	%xmm7, %xmm0
     -      -     0.99   0.01    -      -      -      -      -      -     addps	%xmm5, %xmm0
    ```

```c++
glm::vec4 motor_application(glm::dualquat const& a, glm::vec4 const& b)
{
    return glm::mat3x4_cast(a) * b;
}
```

??? note "GLM LLVM-MCA assembly and analysis"

    ```
    Iterations:        100
    Instructions:      14100
    Total Cycles:      5435
    Total uOps:        15700

    Dispatch Width:    6
    uOps Per Cycle:    2.89
    IPC:               2.59
    Block RThroughput: 38.5


    Instruction Info:
    [1]: #uOps
    [2]: Latency
    [3]: RThroughput
    [4]: MayLoad
    [5]: MayStore
    [6]: HasSideEffects (U)

    [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
     1      5     0.50    *                   movss	4(%rdi), %xmm1
     1      5     0.50    *                   movss	(%rdi), %xmm2
     1      5     0.50    *                   movss	8(%rdi), %xmm15
     1      5     0.50    *                   movss	12(%rdi), %xmm7
     1      1     0.33                        movaps	%xmm2, %xmm3
     1      1     0.33                        movaps	%xmm1, %xmm0
     1      1     0.33                        movaps	%xmm1, %xmm6
     1      5     0.50    *                   movss	(%rsi), %xmm10
     1      4     0.50                        mulss	%xmm1, %xmm0
     1      1     0.33                        movaps	%xmm7, %xmm5
     1      1     0.33                        movaps	%xmm2, %xmm4
     1      5     0.50    *                   movss	4(%rsi), %xmm9
     1      4     0.50                        mulss	%xmm2, %xmm3
     1      1     0.33                        movaps	%xmm15, %xmm14
     1      1     0.33                        movaps	%xmm2, %xmm11
     1      5     0.50    *                   movss	8(%rsi), %xmm8
     1      1     0.33                        movaps	%xmm15, %xmm12
     1      1     0.33                        movaps	%xmm15, %xmm13
     1      4     0.50                        addss	%xmm0, %xmm3
     1      1     0.33                        movaps	%xmm15, %xmm0
     1      4     0.50                        mulss	%xmm15, %xmm0
     1      4     0.50                        addss	%xmm0, %xmm3
     1      1     0.33                        movaps	%xmm7, %xmm0
     1      4     0.50                        mulss	%xmm7, %xmm0
     1      4     0.50                        addss	%xmm0, %xmm3
     1      1     0.33                        movaps	%xmm15, %xmm0
     1      11    3.00                        divss	%xmm3, %xmm5
     1      11    3.00                        divss	%xmm3, %xmm6
     1      11    3.00                        divss	%xmm3, %xmm4
     1      11    3.00                        divss	%xmm3, %xmm14
     1      1     0.33                        movaps	%xmm5, %xmm3
     1      1     0.33                        movaps	%xmm1, %xmm5
     1      4     0.50                        mulss	%xmm6, %xmm5
     1      4     0.50                        addss	%xmm6, %xmm6
     1      4     0.50                        mulss	%xmm3, %xmm7
     1      4     0.50                        addss	%xmm3, %xmm3
     1      4     0.50                        mulss	%xmm4, %xmm11
     1      4     0.50                        addss	%xmm4, %xmm4
     1      4     0.50                        mulss	%xmm6, %xmm13
     2      1     1.00           *            movss	%xmm5, -56(%rsp)
     1      4     0.50                        mulss	%xmm3, %xmm2
     1      1     0.33                        movaps	%xmm1, %xmm5
     1      4     0.50                        mulss	%xmm3, %xmm1
     1      4     0.50                        mulss	%xmm4, %xmm12
     2      1     1.00           *            movss	%xmm11, -40(%rsp)
     1      4     0.50                        mulss	%xmm4, %xmm5
     1      5     0.50    *                   movss	24(%rdi), %xmm11
     2      1     1.00           *            movss	%xmm13, -16(%rsp)
     1      4     0.50                        mulss	%xmm3, %xmm15
     1      5     0.50    *                   movss	16(%rdi), %xmm13
     2      1     1.00           *            movss	%xmm2, -24(%rsp)
     2      1     1.00           *            movss	%xmm1, -20(%rsp)
     1      5     0.50    *                   movss	28(%rdi), %xmm1
     2      1     1.00           *            movss	%xmm12, -28(%rsp)
     1      5     0.50    *                   movss	20(%rdi), %xmm12
     2      1     1.00           *            movss	%xmm1, -12(%rsp)
     1      4     0.50                        mulss	%xmm14, %xmm0
     1      4     0.50                        addss	%xmm14, %xmm14
     1      5     0.50    *                   movss	-40(%rsp), %xmm1
     1      1     0.33                        movaps	%xmm5, %xmm2
     1      4     0.50                        subss	%xmm15, %xmm5
     1      4     0.50                        addss	%xmm15, %xmm2
     1      5     0.50    *                   movss	-16(%rsp), %xmm15
     1      4     0.50                        addss	%xmm7, %xmm1
     2      9     0.50    *                   subss	-56(%rsp), %xmm1
     1      4     0.50                        mulss	%xmm10, %xmm5
     1      4     0.50                        mulss	%xmm9, %xmm2
     1      4     0.50                        subss	%xmm0, %xmm1
     1      4     0.50                        mulss	%xmm10, %xmm1
     1      4     0.50                        addss	%xmm2, %xmm1
     1      5     0.50    *                   movss	-28(%rsp), %xmm2
     2      9     0.50    *                   subss	-20(%rsp), %xmm2
     1      4     0.50                        mulss	%xmm8, %xmm2
     1      4     0.50                        addss	%xmm2, %xmm1
     1      5     0.50    *                   movss	-56(%rsp), %xmm2
     1      4     0.50                        addss	%xmm7, %xmm2
     2      9     0.50    *                   subss	-40(%rsp), %xmm2
     1      4     0.50                        subss	%xmm0, %xmm2
     1      4     0.50                        addss	%xmm7, %xmm0
     1      1     0.33                        movaps	%xmm3, %xmm7
     2      9     0.50    *                   subss	-40(%rsp), %xmm0
     2      9     0.50    *                   subss	-56(%rsp), %xmm0
     1      4     0.50                        mulss	%xmm13, %xmm7
     1      4     0.50                        mulss	%xmm9, %xmm2
     1      4     0.50                        addss	%xmm5, %xmm2
     1      5     0.50    *                   movss	-24(%rsp), %xmm5
     1      4     0.50                        addss	%xmm15, %xmm5
     2      9     0.50    *                   subss	-24(%rsp), %xmm15
     1      4     0.50                        mulss	%xmm8, %xmm5
     1      4     0.50                        mulss	%xmm9, %xmm15
     1      4     0.50                        addss	%xmm5, %xmm2
     1      5     0.50    *                   movss	-28(%rsp), %xmm5
     2      9     0.50    *                   addss	-20(%rsp), %xmm5
     1      4     0.50                        mulss	%xmm10, %xmm5
     1      1     1.00                        unpcklps	%xmm2, %xmm1
     1      4     0.50                        addss	%xmm15, %xmm5
     1      1     0.33                        movaps	%xmm0, %xmm15
     1      4     0.50                        mulss	%xmm8, %xmm15
     1      4     0.50                        addss	%xmm15, %xmm5
     1      5     0.50    *                   movss	-12(%rsp), %xmm15
     1      1     0.33                        movaps	%xmm15, %xmm0
     1      4     0.50                        mulss	%xmm4, %xmm0
     1      4     0.50                        subss	%xmm7, %xmm0
     1      1     0.33                        movaps	%xmm14, %xmm7
     1      4     0.50                        mulss	%xmm12, %xmm7
     1      4     0.50                        addss	%xmm7, %xmm0
     1      1     0.33                        movaps	%xmm6, %xmm7
     1      4     0.50                        mulss	%xmm11, %xmm7
     1      4     0.50                        subss	%xmm7, %xmm0
     1      1     0.33                        movaps	%xmm14, %xmm7
     1      4     0.50                        mulss	%xmm13, %xmm7
     1      4     0.50                        mulss	%xmm15, %xmm14
     1      4     0.50                        mulss	%xmm0, %xmm10
     1      1     0.33                        movaps	%xmm15, %xmm0
     1      4     0.50                        mulss	%xmm6, %xmm0
     1      4     0.50                        mulss	%xmm13, %xmm6
     1      4     0.50                        subss	%xmm7, %xmm0
     1      1     0.33                        movaps	%xmm3, %xmm7
     1      4     0.50                        mulss	%xmm12, %xmm7
     1      4     0.50                        addss	%xmm6, %xmm14
     1      1     0.33                        movaps	%xmm1, %xmm6
     1      4     0.50                        mulss	%xmm11, %xmm3
     1      4     0.50                        subss	%xmm7, %xmm0
     1      1     0.33                        movaps	%xmm4, %xmm7
     1      4     0.50                        mulss	%xmm12, %xmm4
     1      4     0.50                        mulss	%xmm11, %xmm7
     1      4     0.50                        subss	%xmm4, %xmm14
     1      4     0.50                        addss	%xmm7, %xmm0
     2      7     0.50    *                   xorps	.LC0(%rip), %xmm0
     1      4     0.50                        subss	%xmm3, %xmm14
     1      4     0.50                        mulss	%xmm0, %xmm9
     1      4     0.50                        mulss	%xmm14, %xmm8
     1      4     0.50                        subss	%xmm10, %xmm9
     1      4     0.50                        subss	%xmm8, %xmm9
     1      1     1.00                        unpcklps	%xmm9, %xmm5
     1      1     1.00                        movlhps	%xmm5, %xmm6
     2      1     1.00           *            movaps	%xmm6, -56(%rsp)
     1      5     0.50    *                   movq	-48(%rsp), %rax
     1      5     0.50    *                   movq	-56(%rsp), %xmm0
     1      1     1.00                        movq	%rax, %xmm1
     1      1     1.00           *            movq	%rax, -40(%rsp)


    Resources:
    [0]   - SKLDivider
    [1]   - SKLFPDivider
    [2]   - SKLPort0
    [3]   - SKLPort1
    [4]   - SKLPort2
    [5]   - SKLPort3
    [6]   - SKLPort4
    [7]   - SKLPort5
    [8]   - SKLPort6
    [9]   - SKLPort7


    Resource pressure per iteration:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]
     -     12.00  41.03  41.04  15.49  15.51  9.00   29.93   -     6.00

    Resource pressure by instruction:
    [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    Instructions:
     -      -      -      -     0.50   0.50    -      -      -      -     movss	4(%rdi), %xmm1
     -      -      -      -     0.50   0.50    -      -      -      -     movss	(%rdi), %xmm2
     -      -      -      -     0.50   0.50    -      -      -      -     movss	8(%rdi), %xmm15
     -      -      -      -     0.50   0.50    -      -      -      -     movss	12(%rdi), %xmm7
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm2, %xmm3
     -      -      -     0.01    -      -      -     0.99    -      -     movaps	%xmm1, %xmm0
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm1, %xmm6
     -      -      -      -     0.50   0.50    -      -      -      -     movss	(%rsi), %xmm10
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm1, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm7, %xmm5
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm2, %xmm4
     -      -      -      -     0.50   0.50    -      -      -      -     movss	4(%rsi), %xmm9
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm2, %xmm3
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm15, %xmm14
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm2, %xmm11
     -      -      -      -     0.49   0.51    -      -      -      -     movss	8(%rsi), %xmm8
     -      -     0.99    -      -      -      -     0.01    -      -     movaps	%xmm15, %xmm12
     -      -      -     0.01    -      -      -     0.99    -      -     movaps	%xmm15, %xmm13
     -      -     0.99   0.01    -      -      -      -      -      -     addss	%xmm0, %xmm3
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm15, %xmm0
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm15, %xmm0
     -      -     0.99   0.01    -      -      -      -      -      -     addss	%xmm0, %xmm3
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm7, %xmm0
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm7, %xmm0
     -      -     0.01   0.99    -      -      -      -      -      -     addss	%xmm0, %xmm3
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm15, %xmm0
     -     3.00   1.00    -      -      -      -      -      -      -     divss	%xmm3, %xmm5
     -     3.00   1.00    -      -      -      -      -      -      -     divss	%xmm3, %xmm6
     -     3.00   1.00    -      -      -      -      -      -      -     divss	%xmm3, %xmm4
     -     3.00   1.00    -      -      -      -      -      -      -     divss	%xmm3, %xmm14
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm5, %xmm3
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm1, %xmm5
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm6, %xmm5
     -      -     1.00    -      -      -      -      -      -      -     addss	%xmm6, %xmm6
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm3, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     addss	%xmm3, %xmm3
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm4, %xmm11
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm4, %xmm4
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm6, %xmm13
     -      -      -      -      -     0.99   1.00    -      -     0.01   movss	%xmm5, -56(%rsp)
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm3, %xmm2
     -      -     0.01    -      -      -      -     0.99    -      -     movaps	%xmm1, %xmm5
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm3, %xmm1
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm4, %xmm12
     -      -      -      -     0.99    -     1.00    -      -     0.01   movss	%xmm11, -40(%rsp)
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm4, %xmm5
     -      -      -      -     0.51   0.49    -      -      -      -     movss	24(%rdi), %xmm11
     -      -      -      -      -     0.01   1.00    -      -     0.99   movss	%xmm13, -16(%rsp)
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm3, %xmm15
     -      -      -      -     0.49   0.51    -      -      -      -     movss	16(%rdi), %xmm13
     -      -      -      -     0.01   0.99   1.00    -      -      -     movss	%xmm2, -24(%rsp)
     -      -      -      -      -      -     1.00    -      -     1.00   movss	%xmm1, -20(%rsp)
     -      -      -      -     0.51   0.49    -      -      -      -     movss	28(%rdi), %xmm1
     -      -      -      -      -      -     1.00    -      -     1.00   movss	%xmm12, -28(%rsp)
     -      -      -      -     0.49   0.51    -      -      -      -     movss	20(%rdi), %xmm12
     -      -      -      -      -      -     1.00    -      -     1.00   movss	%xmm1, -12(%rsp)
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm14, %xmm0
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm14, %xmm14
     -      -      -      -     0.51   0.49    -      -      -      -     movss	-40(%rsp), %xmm1
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm5, %xmm2
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm15, %xmm5
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm15, %xmm2
     -      -      -      -     0.50   0.50    -      -      -      -     movss	-16(%rsp), %xmm15
     -      -     1.00    -      -      -      -      -      -      -     addss	%xmm7, %xmm1
     -      -      -     1.00   0.99   0.01    -      -      -      -     subss	-56(%rsp), %xmm1
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm10, %xmm5
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm9, %xmm2
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm0, %xmm1
     -      -     0.01   0.99    -      -      -      -      -      -     mulss	%xmm10, %xmm1
     -      -     0.01   0.99    -      -      -      -      -      -     addss	%xmm2, %xmm1
     -      -      -      -     0.50   0.50    -      -      -      -     movss	-28(%rsp), %xmm2
     -      -     1.00    -     0.49   0.51    -      -      -      -     subss	-20(%rsp), %xmm2
     -      -     0.01   0.99    -      -      -      -      -      -     mulss	%xmm8, %xmm2
     -      -     0.01   0.99    -      -      -      -      -      -     addss	%xmm2, %xmm1
     -      -      -      -     0.51   0.49    -      -      -      -     movss	-56(%rsp), %xmm2
     -      -     1.00    -      -      -      -      -      -      -     addss	%xmm7, %xmm2
     -      -      -     1.00   0.50   0.50    -      -      -      -     subss	-40(%rsp), %xmm2
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm0, %xmm2
     -      -     1.00    -      -      -      -      -      -      -     addss	%xmm7, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm3, %xmm7
     -      -     1.00    -     0.50   0.50    -      -      -      -     subss	-40(%rsp), %xmm0
     -      -     1.00    -     0.50   0.50    -      -      -      -     subss	-56(%rsp), %xmm0
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm13, %xmm7
     -      -     0.01   0.99    -      -      -      -      -      -     mulss	%xmm9, %xmm2
     -      -     0.01   0.99    -      -      -      -      -      -     addss	%xmm5, %xmm2
     -      -      -      -     0.50   0.50    -      -      -      -     movss	-24(%rsp), %xmm5
     -      -     0.99   0.01    -      -      -      -      -      -     addss	%xmm15, %xmm5
     -      -     1.00    -     0.50   0.50    -      -      -      -     subss	-24(%rsp), %xmm15
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm8, %xmm5
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm9, %xmm15
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm5, %xmm2
     -      -      -      -     0.50   0.50    -      -      -      -     movss	-28(%rsp), %xmm5
     -      -      -     1.00   0.50   0.50    -      -      -      -     addss	-20(%rsp), %xmm5
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm10, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     unpcklps	%xmm2, %xmm1
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm15, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm0, %xmm15
     -      -     0.01   0.99    -      -      -      -      -      -     mulss	%xmm8, %xmm15
     -      -     0.01   0.99    -      -      -      -      -      -     addss	%xmm15, %xmm5
     -      -      -      -     0.50   0.50    -      -      -      -     movss	-12(%rsp), %xmm15
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm15, %xmm0
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm4, %xmm0
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm7, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm14, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm12, %xmm7
     -      -      -     1.00    -      -      -      -      -      -     addss	%xmm7, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm6, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm11, %xmm7
     -      -     0.99   0.01    -      -      -      -      -      -     subss	%xmm7, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm14, %xmm7
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm13, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm15, %xmm14
     -      -     0.99   0.01    -      -      -      -      -      -     mulss	%xmm0, %xmm10
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm15, %xmm0
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm6, %xmm0
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm13, %xmm6
     -      -     1.00    -      -      -      -      -      -      -     subss	%xmm7, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm3, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm12, %xmm7
     -      -     1.00    -      -      -      -      -      -      -     addss	%xmm6, %xmm14
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm1, %xmm6
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm11, %xmm3
     -      -     0.99   0.01    -      -      -      -      -      -     subss	%xmm7, %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movaps	%xmm4, %xmm7
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm12, %xmm4
     -      -     1.00    -      -      -      -      -      -      -     mulss	%xmm11, %xmm7
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm4, %xmm14
     -      -     0.99   0.01    -      -      -      -      -      -     addss	%xmm7, %xmm0
     -      -      -      -     0.50   0.50    -     1.00    -      -     xorps	.LC0(%rip), %xmm0
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm3, %xmm14
     -      -      -     1.00    -      -      -      -      -      -     mulss	%xmm0, %xmm9
     -      -     0.01   0.99    -      -      -      -      -      -     mulss	%xmm14, %xmm8
     -      -     1.00    -      -      -      -      -      -      -     subss	%xmm10, %xmm9
     -      -      -     1.00    -      -      -      -      -      -     subss	%xmm8, %xmm9
     -      -      -      -      -      -      -     1.00    -      -     unpcklps	%xmm9, %xmm5
     -      -      -      -      -      -      -     1.00    -      -     movlhps	%xmm5, %xmm6
     -      -      -      -      -      -     1.00    -      -     1.00   movaps	%xmm6, -56(%rsp)
     -      -      -      -     0.50   0.50    -      -      -      -     movq	-48(%rsp), %rax
     -      -      -      -     0.50   0.50    -      -      -      -     movq	-56(%rsp), %xmm0
     -      -      -      -      -      -      -     1.00    -      -     movq	%rax, %xmm1
     -      -      -      -      -     0.01   1.00    -      -     0.99   movq	%rax, -40(%rsp)
    ```

!!! note

    An RTM implementation of the dual-quat application is not provided (internally, RTM uses a type called `qvvf` which stores scale, translation, and rotation as separate components). The `qvvf` cannot be interpolated the same way as a motor or dual quaternion so it is omitted from this portion of the analysis.
