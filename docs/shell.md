In the [`sym`](https://github.com/jeremyong/Klein/tree/master/sym) directory resides
code for a lightweight computer algebra system that can evaluate geometric algebra
expressions symbolically. This tool was used to validate the implementation of
Klein and verify various optimizations in its SSE routines (nearly every operation
is fully vectorized).

The tool is compiled by default as the executable `klein_shell` when Klein is built
as a standalone project. If you wish to enable it if transitively including the
project, you'll need to set the CMake option `KLEIN_BUILD_SYM` to `ON`.

To use the shell, you can either run it interactively from a terminal, or you can
pipe text files to it. For example, suppose we had a file that looked like:

```
# test.klein
# My klein test

(a0 e123 + a1 e021 + a2 e013 + a3 e032) * (b0 + b1 e12 + b2 e31 + b3 e23)
```

Running the command `cat test.klein | ./klein_shell` will produce the following
output:

```
# test.klein
# My klein test

a0 b0 e0 + -a0 b3 e012 + a0 b2 e013 + -a0 b1 e023
```

Whitespace and lines starting with a `#` are echoed back in the output and the
expressions provided are evaluated and simplified symbolically. Numerical constants
are permitted.

The grammar is relatively simple and the Klein shell is a work in progress.
Several examples are provided in the repository to examine to understand proper
usage. They are stored in the [`scripts`](https://github.com/jeremyong/Klein/tree/master/scripts)
folder and are used to both demonstrate GA concepts and validate existing code
and test cases.
