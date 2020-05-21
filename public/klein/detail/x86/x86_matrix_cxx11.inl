// Implementation file for C++11 compatibility

template <bool Translate, bool Normalized>
KLN_INLINE void KLN_VEC_CALL mat4x4_12(__m128 b,
                                       __m128 const* c,
                                       __m128* out) noexcept;

template <>
KLN_INLINE void KLN_VEC_CALL mat4x4_12<true, true>(__m128 b,
                                                   __m128 const* c,
                                                   __m128* out) noexcept
{
    float buf[4];
    _mm_storeu_ps(buf, _mm_mul_ps(b, b));
    float b0_2 = buf[0];
    float b1_2 = buf[1];
    float b2_2 = buf[2];
    float b3_2 = buf[3];

    __m128& c0 = out[0];
    c0         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 0, 2, 0));
    __m128 tmp
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 1), KLN_SWIZZLE(b, 0, 3, 0, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, 0.f, -0.f, 0.f), tmp);
    c0  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 1.f), _mm_add_ps(c0, tmp));
    c0  = _mm_sub_ps(c0, _mm_set_ss(b3_2 + b2_2));

    __m128& c1 = out[1];
    c1         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 3, 1, 3));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 3, 2), KLN_SWIZZLE(b, 0, 1, 3, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, 0.f), tmp);
    c1  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, -1.f, 2.f), _mm_add_ps(c1, tmp));
    c1  = _mm_add_ps(c1, _mm_set_ps(0.f, 0.f, b0_2 + b2_2, 0.f));

    __m128& c2 = out[2];
    c2         = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, -0.f),
                    _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 2, 0, 2)));
    c2         = _mm_add_ps(
        c2, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 2, 1), KLN_SWIZZLE(b, 0, 0, 3, 3)));
    c2 = _mm_mul_ps(c2, _mm_set_ps(0.f, 1.f, 2.f, 2.f));
    c2 = _mm_add_ps(c2, _mm_set_ps(0.f, b3_2 - b1_2, 0.f, 0.f));

    __m128& c3 = out[3];
    c3         = _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 1, 3, 1));
    c3         = _mm_add_ps(
        c3, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3), KLN_SWIZZLE(*c, 0, 3, 2, 2)));
    c3 = _mm_add_ps(
        c3, _mm_mul_ps(KLN_SWIZZLE(b, 0, 3, 2, 1), KLN_SWIZZLE(*c, 0, 0, 0, 0)));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 2), KLN_SWIZZLE(*c, 0, 2, 1, 3));
    c3  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 2.f), _mm_sub_ps(tmp, c3));

#ifdef KLEIN_SSE_4_1
    c3 = _mm_blend_ps(c3, _mm_set_ps(1.f, 0.f, 0.f, 0.f), 0b1000);
#else
    c3 = _mm_add_ps(c3, _mm_set_ps(1.f, 0.f, 0.f, 0.f));
#endif
}

template <>
KLN_INLINE void KLN_VEC_CALL mat4x4_12<true, false>(__m128 b,
                                                    __m128 const* c,
                                                    __m128* out) noexcept
{
    float buf[4];
    _mm_storeu_ps(buf, _mm_mul_ps(b, b));
    float b0_2 = buf[0];
    float b1_2 = buf[1];
    float b2_2 = buf[2];
    float b3_2 = buf[3];

    __m128& c0 = out[0];
    c0         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 0, 2, 0));
    __m128 tmp
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 1), KLN_SWIZZLE(b, 0, 3, 0, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, 0.f, -0.f, 0.f), tmp);
    c0  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 1.f), _mm_add_ps(c0, tmp));
    c0  = _mm_sub_ps(c0, _mm_set_ss(b3_2 + b2_2));

    __m128& c1 = out[1];
    c1         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 3, 1, 3));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 3, 2), KLN_SWIZZLE(b, 0, 1, 3, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, 0.f), tmp);
    c1  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, -1.f, 2.f), _mm_add_ps(c1, tmp));
    c1  = _mm_add_ps(c1, _mm_set_ps(0.f, 0.f, b0_2 + b2_2, 0.f));

    __m128& c2 = out[2];
    c2         = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, -0.f),
                    _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 2, 0, 2)));
    c2         = _mm_add_ps(
        c2, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 2, 1), KLN_SWIZZLE(b, 0, 0, 3, 3)));
    c2 = _mm_mul_ps(c2, _mm_set_ps(0.f, 1.f, 2.f, 2.f));
    c2 = _mm_add_ps(c2, _mm_set_ps(0.f, b3_2 - b1_2, 0.f, 0.f));

    __m128& c3 = out[3];
    c3         = _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 1, 3, 1));
    c3         = _mm_add_ps(
        c3, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3), KLN_SWIZZLE(*c, 0, 3, 2, 2)));
    c3 = _mm_add_ps(
        c3, _mm_mul_ps(KLN_SWIZZLE(b, 0, 3, 2, 1), KLN_SWIZZLE(*c, 0, 0, 0, 0)));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 2), KLN_SWIZZLE(*c, 0, 2, 1, 3));
    c3  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 2.f), _mm_sub_ps(tmp, c3));

#ifdef KLEIN_SSE_4_1
    c3 = _mm_blend_ps(
        c3, _mm_set_ps(b0_2 + b1_2 + b2_2 + b3_2, 0.f, 0.f, 0.f), 0b1000);
#else
    c3 = _mm_add_ps(c3, _mm_set_ps(b0_2 + b1_2 + b2_2 + b3_2, 0.f, 0.f, 0.f));
#endif
}

template <>
KLN_INLINE void KLN_VEC_CALL mat4x4_12<false, true>(__m128 b,
                                                    __m128 const* c,
                                                    __m128* out) noexcept
{
    float buf[4];
    _mm_storeu_ps(buf, _mm_mul_ps(b, b));
    float b0_2 = buf[0];
    float b1_2 = buf[1];
    float b2_2 = buf[2];
    float b3_2 = buf[3];

    __m128& c0 = out[0];
    c0         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 0, 2, 0));
    __m128 tmp
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 1), KLN_SWIZZLE(b, 0, 3, 0, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, 0.f, -0.f, 0.f), tmp);
    c0  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 1.f), _mm_add_ps(c0, tmp));
    c0  = _mm_sub_ps(c0, _mm_set_ss(b3_2 + b2_2));

    __m128& c1 = out[1];
    c1         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 3, 1, 3));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 3, 2), KLN_SWIZZLE(b, 0, 1, 3, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, 0.f), tmp);
    c1  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, -1.f, 2.f), _mm_add_ps(c1, tmp));
    c1  = _mm_add_ps(c1, _mm_set_ps(0.f, 0.f, b0_2 + b2_2, 0.f));

    __m128& c2 = out[2];
    c2         = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, -0.f),
                    _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 2, 0, 2)));
    c2         = _mm_add_ps(
        c2, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 2, 1), KLN_SWIZZLE(b, 0, 0, 3, 3)));
    c2 = _mm_mul_ps(c2, _mm_set_ps(0.f, 1.f, 2.f, 2.f));
    c2 = _mm_add_ps(c2, _mm_set_ps(0.f, b3_2 - b1_2, 0.f, 0.f));

    __m128& c3 = out[3];
#ifdef KLEIN_SSE_4_1
    c3 = _mm_blend_ps(c3, _mm_set_ps(1.f, 0.f, 0.f, 0.f), 0b1000);
#else
    c3 = _mm_add_ps(c3, _mm_set_ps(1.f, 0.f, 0.f, 0.f));
#endif
}

template <>
KLN_INLINE void KLN_VEC_CALL mat4x4_12<false, false>(__m128 b,
                                                     __m128 const* c,
                                                     __m128* out) noexcept
{
    float buf[4];
    _mm_storeu_ps(buf, _mm_mul_ps(b, b));
    float b0_2 = buf[0];
    float b1_2 = buf[1];
    float b2_2 = buf[2];
    float b3_2 = buf[3];

    __m128& c0 = out[0];
    c0         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 0, 2, 0));
    __m128 tmp
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 1), KLN_SWIZZLE(b, 0, 3, 0, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, 0.f, -0.f, 0.f), tmp);
    c0  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 1.f), _mm_add_ps(c0, tmp));
    c0  = _mm_sub_ps(c0, _mm_set_ss(b3_2 + b2_2));

    __m128& c1 = out[1];
    c1         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 3, 1, 3));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 3, 2), KLN_SWIZZLE(b, 0, 1, 3, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, 0.f), tmp);
    c1  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, -1.f, 2.f), _mm_add_ps(c1, tmp));
    c1  = _mm_add_ps(c1, _mm_set_ps(0.f, 0.f, b0_2 + b2_2, 0.f));

    __m128& c2 = out[2];
    c2         = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, -0.f),
                    _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 2, 0, 2)));
    c2         = _mm_add_ps(
        c2, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 2, 1), KLN_SWIZZLE(b, 0, 0, 3, 3)));
    c2 = _mm_mul_ps(c2, _mm_set_ps(0.f, 1.f, 2.f, 2.f));
    c2 = _mm_add_ps(c2, _mm_set_ps(0.f, b3_2 - b1_2, 0.f, 0.f));

    __m128& c3 = out[3];
#ifdef KLEIN_SSE_4_1
    c3 = _mm_blend_ps(
        c3, _mm_set_ps(b0_2 + b1_2 + b2_2 + b3_2, 0.f, 0.f, 0.f), 0b1000);
#else
    c3 = _mm_add_ps(c3, _mm_set_ps(b0_2 + b1_2 + b2_2 + b3_2, 0.f, 0.f, 0.f));
#endif
}