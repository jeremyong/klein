// Implementation file for C++11 compatibility

template <bool Variadic, bool Translate, bool InputP2>
KLN_INLINE void KLN_VEC_CALL swMM(__m128 const* KLN_RESTRICT in,
                                  __m128 const& KLN_RESTRICT b,
                                  __m128 const* KLN_RESTRICT c,
                                  __m128* out,
                                  size_t count = 0) noexcept;

template <>
KLN_INLINE void KLN_VEC_CALL swMM<true, true, true>(__m128 const* KLN_RESTRICT in,
                                                    __m128 const& KLN_RESTRICT b,
                                                    __m128 const* KLN_RESTRICT c,
                                                    __m128* out,
                                                    size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    __m128 czero  = KLN_SWIZZLE(*c, 0, 0, 0, 0);
    __m128 c_xzwy = KLN_SWIZZLE(*c, 1, 3, 2, 0);
    __m128 c_xwyz = KLN_SWIZZLE(*c, 2, 1, 3, 0);

    __m128 tmp4 = _mm_mul_ps(b, *c);
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_yxxx, KLN_SWIZZLE(*c, 0, 0, 0, 1)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 3, 2), KLN_SWIZZLE(*c, 1, 3, 3, 2)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 2, 3), KLN_SWIZZLE(*c, 2, 1, 2, 3)));
    tmp4 = _mm_add_ps(tmp4, tmp4);

    __m128 tmp5 = _mm_mul_ps(b, c_xwyz);
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xzwy, czero));
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xwyz, *c));
    tmp5        = _mm_sub_ps(tmp5, _mm_mul_ps(b_xxxx, c_xzwy));
    tmp5        = _mm_mul_ps(tmp5, scale);

    __m128 tmp6 = _mm_mul_ps(b, c_xzwy);
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xxxx, c_xwyz));
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xzwy, *c));
    tmp6        = _mm_sub_ps(tmp6, _mm_mul_ps(b_xwyz, czero));
    tmp6        = _mm_mul_ps(tmp6, scale);

    for (size_t i = 0; i != count; ++i)
    {
        __m128 const& p1_in = in[2 * i]; // a
        __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
        __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

        __m128& p1_out = out[2 * i];

        p1_out = _mm_mul_ps(tmp, p1_in);
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

        __m128 const& p2_in = in[2 * i + 1]; // d
        __m128& p2_out      = out[2 * i + 1];
        p2_out              = _mm_mul_ps(tmp, p2_in);
        p2_out              = _mm_add_ps(
            p2_out, _mm_mul_ps(tmp2, KLN_SWIZZLE(p2_in, 1, 3, 2, 0)));
        p2_out = _mm_add_ps(
            p2_out, _mm_mul_ps(tmp3, KLN_SWIZZLE(p2_in, 2, 1, 3, 0)));

        p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp4, p1_in));
        p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp5, p1_in_xwyz));
        p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp6, p1_in_xzwy));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL swMM<true, true, false>(__m128 const* KLN_RESTRICT in,
                                                     __m128 const& KLN_RESTRICT b,
                                                     __m128 const* KLN_RESTRICT c,
                                                     __m128* out,
                                                     size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    __m128 czero  = KLN_SWIZZLE(*c, 0, 0, 0, 0);
    __m128 c_xzwy = KLN_SWIZZLE(*c, 1, 3, 2, 0);
    __m128 c_xwyz = KLN_SWIZZLE(*c, 2, 1, 3, 0);

    __m128 tmp4 = _mm_mul_ps(b, *c);
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_yxxx, KLN_SWIZZLE(*c, 0, 0, 0, 1)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 3, 2), KLN_SWIZZLE(*c, 1, 3, 3, 2)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 2, 3), KLN_SWIZZLE(*c, 2, 1, 2, 3)));
    tmp4 = _mm_add_ps(tmp4, tmp4);

    __m128 tmp5 = _mm_mul_ps(b, c_xwyz);
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xzwy, czero));
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xwyz, *c));
    tmp5        = _mm_sub_ps(tmp5, _mm_mul_ps(b_xxxx, c_xzwy));
    tmp5        = _mm_mul_ps(tmp5, scale);

    __m128 tmp6 = _mm_mul_ps(b, c_xzwy);
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xxxx, c_xwyz));
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xzwy, *c));
    tmp6        = _mm_sub_ps(tmp6, _mm_mul_ps(b_xwyz, czero));
    tmp6        = _mm_mul_ps(tmp6, scale);

    for (size_t i = 0; i != count; ++i)
    {
        __m128 const& p1_in = in[i]; // a
        __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
        __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

        __m128& p1_out = out[i];

        p1_out = _mm_mul_ps(tmp, p1_in);
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

        __m128& p2_out = out[2 * i + 1];
        p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp4, p1_in));
        p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp5, p1_in_xwyz));
        p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp6, p1_in_xzwy));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL swMM<true, false, true>(__m128 const* KLN_RESTRICT in,
                                                     __m128 const& KLN_RESTRICT b,
                                                     __m128 const* KLN_RESTRICT c,
                                                     __m128* out,
                                                     size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    for (size_t i = 0; i != count; ++i)
    {
        __m128 const& p1_in = in[2 * i]; // a
        __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
        __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

        __m128& p1_out = out[2 * i];

        p1_out = _mm_mul_ps(tmp, p1_in);
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

        __m128 const& p2_in = in[2 * i + 1]; // d
        __m128& p2_out      = out[2 * i + 1];
        p2_out              = _mm_mul_ps(tmp, p2_in);
        p2_out              = _mm_add_ps(
            p2_out, _mm_mul_ps(tmp2, KLN_SWIZZLE(p2_in, 1, 3, 2, 0)));
        p2_out = _mm_add_ps(
            p2_out, _mm_mul_ps(tmp3, KLN_SWIZZLE(p2_in, 2, 1, 3, 0)));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL
swMM<true, false, false>(__m128 const* KLN_RESTRICT in,
                         __m128 const& KLN_RESTRICT b,
                         __m128 const* KLN_RESTRICT c,
                         __m128* out,
                         size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    for (size_t i = 0; i != count; ++i)
    {
        __m128 const& p1_in = in[i]; // a
        __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
        __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

        __m128& p1_out = out[i];

        p1_out = _mm_mul_ps(tmp, p1_in);
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL swMM<false, true, true>(__m128 const* KLN_RESTRICT in,
                                                     __m128 const& KLN_RESTRICT b,
                                                     __m128 const* KLN_RESTRICT c,
                                                     __m128* out,
                                                     size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    __m128 czero  = KLN_SWIZZLE(*c, 0, 0, 0, 0);
    __m128 c_xzwy = KLN_SWIZZLE(*c, 1, 3, 2, 0);
    __m128 c_xwyz = KLN_SWIZZLE(*c, 2, 1, 3, 0);

    __m128 tmp4 = _mm_mul_ps(b, *c);
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_yxxx, KLN_SWIZZLE(*c, 0, 0, 0, 1)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 3, 2), KLN_SWIZZLE(*c, 1, 3, 3, 2)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 2, 3), KLN_SWIZZLE(*c, 2, 1, 2, 3)));
    tmp4 = _mm_add_ps(tmp4, tmp4);

    __m128 tmp5 = _mm_mul_ps(b, c_xwyz);
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xzwy, czero));
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xwyz, *c));
    tmp5        = _mm_sub_ps(tmp5, _mm_mul_ps(b_xxxx, c_xzwy));
    tmp5        = _mm_mul_ps(tmp5, scale);

    __m128 tmp6 = _mm_mul_ps(b, c_xzwy);
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xxxx, c_xwyz));
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xzwy, *c));
    tmp6        = _mm_sub_ps(tmp6, _mm_mul_ps(b_xwyz, czero));
    tmp6        = _mm_mul_ps(tmp6, scale);

    __m128 const& p1_in = in[0]; // a
    __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
    __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

    __m128& p1_out = out[0];

    p1_out = _mm_mul_ps(tmp, p1_in);
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

    __m128 const& p2_in = in[1]; // d
    __m128& p2_out      = out[1];
    p2_out              = _mm_mul_ps(tmp, p2_in);
    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp2, KLN_SWIZZLE(p2_in, 1, 3, 2, 0)));
    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp3, KLN_SWIZZLE(p2_in, 2, 1, 3, 0)));

    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp4, p1_in));
    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp5, p1_in_xwyz));
    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp6, p1_in_xzwy));
}

template <>
KLN_INLINE void KLN_VEC_CALL
swMM<false, true, false>(__m128 const* KLN_RESTRICT in,
                         __m128 const& KLN_RESTRICT b,
                         __m128 const* KLN_RESTRICT c,
                         __m128* out,
                         size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    __m128 czero  = KLN_SWIZZLE(*c, 0, 0, 0, 0);
    __m128 c_xzwy = KLN_SWIZZLE(*c, 1, 3, 2, 0);
    __m128 c_xwyz = KLN_SWIZZLE(*c, 2, 1, 3, 0);

    __m128 tmp4 = _mm_mul_ps(b, *c);
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_yxxx, KLN_SWIZZLE(*c, 0, 0, 0, 1)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 3, 2), KLN_SWIZZLE(*c, 1, 3, 3, 2)));
    tmp4 = _mm_sub_ps(
        tmp4,
        _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 2, 3), KLN_SWIZZLE(*c, 2, 1, 2, 3)));
    tmp4 = _mm_add_ps(tmp4, tmp4);

    __m128 tmp5 = _mm_mul_ps(b, c_xwyz);
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xzwy, czero));
    tmp5        = _mm_add_ps(tmp5, _mm_mul_ps(b_xwyz, *c));
    tmp5        = _mm_sub_ps(tmp5, _mm_mul_ps(b_xxxx, c_xzwy));
    tmp5        = _mm_mul_ps(tmp5, scale);

    __m128 tmp6 = _mm_mul_ps(b, c_xzwy);
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xxxx, c_xwyz));
    tmp6        = _mm_add_ps(tmp6, _mm_mul_ps(b_xzwy, *c));
    tmp6        = _mm_sub_ps(tmp6, _mm_mul_ps(b_xwyz, czero));
    tmp6        = _mm_mul_ps(tmp6, scale);

    __m128 const& p1_in = in[0]; // a
    __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
    __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

    __m128& p1_out = out[0];

    p1_out = _mm_mul_ps(tmp, p1_in);
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

    __m128& p2_out = out[1];
    p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp4, p1_in));
    p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp5, p1_in_xwyz));
    p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp6, p1_in_xzwy));
}

template <>
KLN_INLINE void KLN_VEC_CALL
swMM<false, false, true>(__m128 const* KLN_RESTRICT in,
                         __m128 const& KLN_RESTRICT b,
                         __m128 const* KLN_RESTRICT c,
                         __m128* out,
                         size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    __m128 const& p1_in = in[0]; // a
    __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
    __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

    __m128& p1_out = out[0];

    p1_out = _mm_mul_ps(tmp, p1_in);
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

    __m128 const& p2_in = in[1]; // d
    __m128& p2_out      = out[1];
    p2_out              = _mm_mul_ps(tmp, p2_in);
    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp2, KLN_SWIZZLE(p2_in, 1, 3, 2, 0)));
    p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp3, KLN_SWIZZLE(p2_in, 2, 1, 3, 0)));
}

template <>
KLN_INLINE void KLN_VEC_CALL
swMM<false, false, false>(__m128 const* KLN_RESTRICT in,
                          __m128 const& KLN_RESTRICT b,
                          __m128 const* KLN_RESTRICT c,
                          __m128* out,
                          size_t count) noexcept
{
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
    __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

    __m128 tmp   = _mm_mul_ps(b, b);
    tmp          = _mm_add_ps(tmp, b_yxxx_2);
    __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
    tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));

    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
    tmp2          = _mm_mul_ps(tmp2, scale);

    __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp3        = _mm_mul_ps(tmp3, scale);

    __m128 const& p1_in = in[0]; // a
    __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
    __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

    __m128& p1_out = out[0];

    p1_out = _mm_mul_ps(tmp, p1_in);
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
    p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));
}

template <bool Variadic, bool Translate>
KLN_INLINE void KLN_VEC_CALL sw012(__m128 const* KLN_RESTRICT a,
                                   __m128 b,
                                   __m128 const* KLN_RESTRICT c,
                                   __m128* out,
                                   size_t count = 0) noexcept;

template <>
KLN_INLINE void KLN_VEC_CALL sw012<true, true>(__m128 const* KLN_RESTRICT a,
                                               __m128 b,
                                               __m128 const* KLN_RESTRICT c,
                                               __m128* out,
                                               size_t count) noexcept
{
    __m128 dc_scale = _mm_set_ps(2.f, 2.f, 2.f, 1.f);
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_xxxx   = KLN_SWIZZLE(b, 0, 0, 0, 0);

    __m128 tmp1
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 2), KLN_SWIZZLE(b, 2, 1, 3, 2));
    tmp1 = _mm_add_ps(
        tmp1, _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 1), KLN_SWIZZLE(b, 3, 2, 1, 1)));
    tmp1 = _mm_mul_ps(tmp1, dc_scale);

    __m128 tmp2 = _mm_mul_ps(b, b_xwyz);

    tmp2 = _mm_sub_ps(tmp2,
                      _mm_xor_ps(_mm_set_ss(-0.f),
                                 _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3),
                                            KLN_SWIZZLE(b, 1, 3, 2, 3))));
    tmp2 = _mm_mul_ps(tmp2, dc_scale);

    __m128 tmp3 = _mm_mul_ps(b, b);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xwyz, b_xwyz));
    tmp3        = _mm_add_ps(tmp3, _mm_mul_ps(b_xxxx, b_xxxx));
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xzwy, b_xzwy));

    __m128 tmp4 = _mm_mul_ps(b_xxxx, *c);
    tmp4 = _mm_add_ps(tmp4, _mm_mul_ps(b_xzwy, KLN_SWIZZLE(*c, 2, 1, 3, 0)));
    tmp4 = _mm_add_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xwyz, KLN_SWIZZLE(*c, 1, 3, 2, 0)));
    tmp4 = _mm_mul_ps(tmp4, dc_scale);

    for (size_t i = 0; i != count; ++i)
    {
        // Compute the lower block for components e1, e2, and e3
        __m128& p = out[i];
        p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 1, 3, 2, 0));
        p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 2, 1, 3, 0)));
        p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));

        __m128 tmp5 = hi_dp(tmp4, a[i]);
        p           = _mm_add_ps(p, tmp5);
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL sw012<true, false>(__m128 const* KLN_RESTRICT a,
                                                __m128 b,
                                                __m128 const* KLN_RESTRICT c,
                                                __m128* out,
                                                size_t count) noexcept
{
    __m128 dc_scale = _mm_set_ps(2.f, 2.f, 2.f, 1.f);
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_xxxx   = KLN_SWIZZLE(b, 0, 0, 0, 0);

    __m128 tmp1
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 2), KLN_SWIZZLE(b, 2, 1, 3, 2));
    tmp1 = _mm_add_ps(
        tmp1, _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 1), KLN_SWIZZLE(b, 3, 2, 1, 1)));
    tmp1 = _mm_mul_ps(tmp1, dc_scale);

    __m128 tmp2 = _mm_mul_ps(b, b_xwyz);

    tmp2 = _mm_sub_ps(tmp2,
                      _mm_xor_ps(_mm_set_ss(-0.f),
                                 _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3),
                                            KLN_SWIZZLE(b, 1, 3, 2, 3))));
    tmp2 = _mm_mul_ps(tmp2, dc_scale);

    __m128 tmp3 = _mm_mul_ps(b, b);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xwyz, b_xwyz));
    tmp3        = _mm_add_ps(tmp3, _mm_mul_ps(b_xxxx, b_xxxx));
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xzwy, b_xzwy));

    for (size_t i = 0; i != count; ++i)
    {
        // Compute the lower block for components e1, e2, and e3
        __m128& p = out[i];
        p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 1, 3, 2, 0));
        p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 2, 1, 3, 0)));
        p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL sw012<false, true>(__m128 const* KLN_RESTRICT a,
                                                __m128 b,
                                                __m128 const* KLN_RESTRICT c,
                                                __m128* out,
                                                size_t count) noexcept
{
    __m128 dc_scale = _mm_set_ps(2.f, 2.f, 2.f, 1.f);
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_xxxx   = KLN_SWIZZLE(b, 0, 0, 0, 0);

    __m128 tmp1
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 2), KLN_SWIZZLE(b, 2, 1, 3, 2));
    tmp1 = _mm_add_ps(
        tmp1, _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 1), KLN_SWIZZLE(b, 3, 2, 1, 1)));
    tmp1 = _mm_mul_ps(tmp1, dc_scale);

    __m128 tmp2 = _mm_mul_ps(b, b_xwyz);

    tmp2 = _mm_sub_ps(tmp2,
                      _mm_xor_ps(_mm_set_ss(-0.f),
                                 _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3),
                                            KLN_SWIZZLE(b, 1, 3, 2, 3))));
    tmp2 = _mm_mul_ps(tmp2, dc_scale);

    __m128 tmp3 = _mm_mul_ps(b, b);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xwyz, b_xwyz));
    tmp3        = _mm_add_ps(tmp3, _mm_mul_ps(b_xxxx, b_xxxx));
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xzwy, b_xzwy));

    __m128 tmp4 = _mm_mul_ps(b_xxxx, *c);
    tmp4 = _mm_add_ps(tmp4, _mm_mul_ps(b_xzwy, KLN_SWIZZLE(*c, 2, 1, 3, 0)));
    tmp4 = _mm_add_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xwyz, KLN_SWIZZLE(*c, 1, 3, 2, 0)));
    tmp4 = _mm_mul_ps(tmp4, dc_scale);

    // Compute the lower block for components e1, e2, and e3
    __m128& p = *out;
    p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(*a, 1, 3, 2, 0));
    p         = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(*a, 2, 1, 3, 0)));
    p         = _mm_add_ps(p, _mm_mul_ps(tmp3, *a));

    __m128 tmp5 = hi_dp(tmp4, *a);
    p           = _mm_add_ps(p, tmp5);
}

template <>
KLN_INLINE void KLN_VEC_CALL sw012<false, false>(__m128 const* KLN_RESTRICT a,
                                                 __m128 b,
                                                 __m128 const* KLN_RESTRICT c,
                                                 __m128* out,
                                                 size_t count) noexcept
{
    __m128 dc_scale = _mm_set_ps(2.f, 2.f, 2.f, 1.f);
    __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
    __m128 b_xxxx   = KLN_SWIZZLE(b, 0, 0, 0, 0);

    __m128 tmp1
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 2), KLN_SWIZZLE(b, 2, 1, 3, 2));
    tmp1 = _mm_add_ps(
        tmp1, _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 1), KLN_SWIZZLE(b, 3, 2, 1, 1)));
    tmp1 = _mm_mul_ps(tmp1, dc_scale);

    __m128 tmp2 = _mm_mul_ps(b, b_xwyz);

    tmp2 = _mm_sub_ps(tmp2,
                      _mm_xor_ps(_mm_set_ss(-0.f),
                                 _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3),
                                            KLN_SWIZZLE(b, 1, 3, 2, 3))));
    tmp2 = _mm_mul_ps(tmp2, dc_scale);

    __m128 tmp3 = _mm_mul_ps(b, b);
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xwyz, b_xwyz));
    tmp3        = _mm_add_ps(tmp3, _mm_mul_ps(b_xxxx, b_xxxx));
    tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xzwy, b_xzwy));

    // Compute the lower block for components e1, e2, and e3
    __m128& p = *out;
    p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(*a, 1, 3, 2, 0));
    p         = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(*a, 2, 1, 3, 0)));
    p         = _mm_add_ps(p, _mm_mul_ps(tmp3, *a));
}

template <bool Variadic, bool Translate>
KLN_INLINE void KLN_VEC_CALL sw312(__m128 const* KLN_RESTRICT a,
                                   __m128 b,
                                   __m128 const* KLN_RESTRICT c,
                                   __m128* out,
                                   size_t count = 0) noexcept;

template <>
KLN_INLINE void KLN_VEC_CALL sw312<true, true>(__m128 const* KLN_RESTRICT a,
                                               __m128 b,
                                               __m128 const* KLN_RESTRICT c,
                                               __m128* out,
                                               size_t count) noexcept
{
    __m128 two    = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 b_xwyz = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy = KLN_SWIZZLE(b, 1, 3, 2, 0);

    __m128 tmp1 = _mm_mul_ps(b, b_xwyz);
    tmp1        = _mm_sub_ps(tmp1, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp1        = _mm_mul_ps(tmp1, two);

    __m128 tmp2 = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2        = _mm_add_ps(tmp2, _mm_mul_ps(b_xzwy, b));
    tmp2        = _mm_mul_ps(tmp2, two);

    __m128 tmp3  = _mm_mul_ps(b, b);
    __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 1);
    tmp3         = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));
    b_tmp        = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp4  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp4         = _mm_add_ps(tmp4, _mm_mul_ps(b_tmp, b_tmp));
    tmp3         = _mm_sub_ps(tmp3, _mm_xor_ps(tmp4, _mm_set_ss(-0.f)));

    tmp4 = _mm_mul_ps(b_xzwy, KLN_SWIZZLE(*c, 2, 1, 3, 0));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xxxx, *c));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xwyz, KLN_SWIZZLE(*c, 1, 3, 2, 0)));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));
    tmp4 = _mm_mul_ps(tmp4, two);

    for (size_t i = 0; i != count; ++i)
    {
        __m128& p = out[i];
        p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 2, 1, 3, 0));
        p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 1, 3, 2, 0)));
        p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));

        p = _mm_add_ps(p, _mm_mul_ps(tmp4, KLN_SWIZZLE(a[i], 0, 0, 0, 0)));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL sw312<true, false>(__m128 const* KLN_RESTRICT a,
                                                __m128 b,
                                                __m128 const* KLN_RESTRICT c,
                                                __m128* out,
                                                size_t count) noexcept
{
    __m128 two    = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 b_xwyz = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy = KLN_SWIZZLE(b, 1, 3, 2, 0);

    __m128 tmp1 = _mm_mul_ps(b, b_xwyz);
    tmp1        = _mm_sub_ps(tmp1, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp1        = _mm_mul_ps(tmp1, two);

    __m128 tmp2 = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2        = _mm_add_ps(tmp2, _mm_mul_ps(b_xzwy, b));
    tmp2        = _mm_mul_ps(tmp2, two);

    __m128 tmp3  = _mm_mul_ps(b, b);
    __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 1);
    tmp3         = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));
    b_tmp        = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp4  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp4         = _mm_add_ps(tmp4, _mm_mul_ps(b_tmp, b_tmp));
    tmp3         = _mm_sub_ps(tmp3, _mm_xor_ps(tmp4, _mm_set_ss(-0.f)));

    for (size_t i = 0; i != count; ++i)
    {
        __m128& p = out[i];
        p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 2, 1, 3, 0));
        p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 1, 3, 2, 0)));
        p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));
    }
}

template <>
KLN_INLINE void KLN_VEC_CALL sw312<false, true>(__m128 const* KLN_RESTRICT a,
                                                __m128 b,
                                                __m128 const* KLN_RESTRICT c,
                                                __m128* out,
                                                size_t count) noexcept
{
    __m128 two    = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 b_xwyz = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy = KLN_SWIZZLE(b, 1, 3, 2, 0);

    __m128 tmp1 = _mm_mul_ps(b, b_xwyz);
    tmp1        = _mm_sub_ps(tmp1, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp1        = _mm_mul_ps(tmp1, two);

    __m128 tmp2 = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2        = _mm_add_ps(tmp2, _mm_mul_ps(b_xzwy, b));
    tmp2        = _mm_mul_ps(tmp2, two);

    __m128 tmp3  = _mm_mul_ps(b, b);
    __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 1);
    tmp3         = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));
    b_tmp        = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp4  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp4         = _mm_add_ps(tmp4, _mm_mul_ps(b_tmp, b_tmp));
    tmp3         = _mm_sub_ps(tmp3, _mm_xor_ps(tmp4, _mm_set_ss(-0.f)));

    tmp4 = _mm_mul_ps(b_xzwy, KLN_SWIZZLE(*c, 2, 1, 3, 0));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xxxx, *c));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xwyz, KLN_SWIZZLE(*c, 1, 3, 2, 0)));
    tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));

    tmp4 = _mm_mul_ps(tmp4, two);

    __m128& p = *out;
    p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(*a, 2, 1, 3, 0));
    p         = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(*a, 1, 3, 2, 0)));
    p         = _mm_add_ps(p, _mm_mul_ps(tmp3, *a));

    p = _mm_add_ps(p, _mm_mul_ps(tmp4, KLN_SWIZZLE(*a, 0, 0, 0, 0)));
}

template <>
KLN_INLINE void KLN_VEC_CALL sw312<false, false>(__m128 const* KLN_RESTRICT a,
                                                 __m128 b,
                                                 __m128 const* KLN_RESTRICT c,
                                                 __m128* out,
                                                 size_t count) noexcept
{
    __m128 two    = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
    __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
    __m128 b_xwyz = KLN_SWIZZLE(b, 2, 1, 3, 0);
    __m128 b_xzwy = KLN_SWIZZLE(b, 1, 3, 2, 0);

    __m128 tmp1 = _mm_mul_ps(b, b_xwyz);
    tmp1        = _mm_sub_ps(tmp1, _mm_mul_ps(b_xxxx, b_xzwy));
    tmp1        = _mm_mul_ps(tmp1, two);

    __m128 tmp2 = _mm_mul_ps(b_xxxx, b_xwyz);
    tmp2        = _mm_add_ps(tmp2, _mm_mul_ps(b_xzwy, b));
    tmp2        = _mm_mul_ps(tmp2, two);

    __m128 tmp3  = _mm_mul_ps(b, b);
    __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 1);
    tmp3         = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));
    b_tmp        = KLN_SWIZZLE(b, 2, 1, 3, 2);
    __m128 tmp4  = _mm_mul_ps(b_tmp, b_tmp);
    b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
    tmp4         = _mm_add_ps(tmp4, _mm_mul_ps(b_tmp, b_tmp));
    tmp3         = _mm_sub_ps(tmp3, _mm_xor_ps(tmp4, _mm_set_ss(-0.f)));
    __m128& p    = *out;
    p            = _mm_mul_ps(tmp1, KLN_SWIZZLE(*a, 2, 1, 3, 0));
    p            = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(*a, 1, 3, 2, 0)));
    p            = _mm_add_ps(p, _mm_mul_ps(tmp3, *a));
}