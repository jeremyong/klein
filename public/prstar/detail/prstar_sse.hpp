// SSE4.1 header
#include <smmintrin.h>

// Little-endian XMM register swizzle
//
// PRS_SWIZZLE(reg, 3, 2, 1, 0) is the identity.
//
// This is undef-ed at the bottom of prstar.hpp so as not to
// pollute the macro namespace
#ifndef PRS_SWIZZLE
#    define PRS_SWIZZLE(reg, x, y, z, w) \
        _mm_shuffle_ps((reg), (reg), _MM_SHUFFLE(x, y, z, w))
#endif