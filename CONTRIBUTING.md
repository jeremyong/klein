# Contributing to Klein

Contributions welcome! Before endeavoring to provide a much appreciated change to
Klein, please read this document to make the process as smooth and as pleasant as
possible.

## Guidelines

1. Before embarking on a large-scale change or architectural improvement, please
   [open an issue](https://github.com/jeremyong/klein/issues) and explain your
   motivation, solution, and plan of attack.
2. If you have questions about how something works or whether something is a
   good idea, you're welcome to join our [discord](https://discordapp.com/invite/mdbAgr)
   to discuss things and get some quick feedback.
3. Please adhere to the `git` and `C++` guidelines below, and don't hesitate to
   ask questions if the process as outlined here is unclear.
4. Understand that all contributions made fall under the project's MIT license.

## Git Workflow

1. A [rebase](https://help.github.com/en/github/using-git/about-git-rebase) workflow
   is the preferred method of keeping your fork/branch up to date with changes. This
   maintains a clean commit history with less bookkeeping needed to isolate problems
   introduced in the context of a linear timeline.
2. Git messages should be as detailed as necessary to describe the change, with an
   imperatively voiced single-line commit title. Refer to
   [this article](https://chris.beams.io/posts/git-commit/) for additional exposition.
3. While a change is under review, don't squash your commits just yet until the review
   is finalized. That way, changes that are committed in response to feedback can be
   indepedently audited.

## C++ Guidelines

1. All names are `snake_case` with the exception of macros which are `UPPER_SNAKE_CASE`.
2. All symbols must reside in the `kln` or `kln::detail` namespaces.
3. Implicit allocations are forbidden
4. New functionality should generally be accompanied with suitable test coverage.
5. If a tradeoff between speed and precision can be made, the fast version is
   preferred and a `_precise` fallback can be provided in addition.
6. Code should abide by the "don't pay for what you don't use" mantra.
7. A recent `clang-format` must be installed and working on your system so that file
   formatting is canonicalized.
8. For functions that return a value, generally `[[nodiscard]]` should be used.
9. All methods and functions should be marked `noexcept` as no code in Klein should need
   to ever `throw`.
10. All variables that are potentially unused should be marked with the `[[maybe_unused]]`
    attribute.
11. Instructions leveraging `AVX` or a more recent instruction set must be behind a
    preprocessor flag named `KLN_ENABLE_ISE_*` ("enable instruction set extension ...").
12. All functions that accept arguments consisting of SIMD registers must be decorated
    with `KLN_VEC_CALL` to enable the vector register calling convention.
13. API documentation is periodically generated from embedded source code comments that
    follow a triple-slash (`///`) so please update documentation accordingly.
14. Be mindful of techniques, idioms, or dependencies that may have an adverse affect on
    compile times. While Klein leverages templates to a certain degree, maintaining lean
    compilation time is a persistent effort.

## Thanks and happy coding!
