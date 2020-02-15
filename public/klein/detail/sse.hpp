// File: sse.hpp
// Purpose: Provide convenience macros and utilities for invoking SSE intrinsics

// SSE4.1 header
#include <smmintrin.h>

// Little-endian XMM register swizzle
//
// KLN_SWIZZLE(reg, 3, 2, 1, 0) is the identity.
//
// This is undef-ed at the bottom of klein.hpp so as not to
// pollute the macro namespace
#ifndef KLN_SWIZZLE
#    define KLN_SWIZZLE(reg, x, y, z, w) \
        _mm_shuffle_ps((reg), (reg), _MM_SHUFFLE(x, y, z, w))
#endif

#ifndef KLN_VEC_CALL
#    ifdef _MSC_VER
// Microsoft Compiler
#        define KLN_VEC_CALL __vectorcall
#    else
// GCC or Clang compiler (sse register passing is on by default)
#        define KLN_VEC_CALL
#    endif
#endif