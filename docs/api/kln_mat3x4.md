## struct `kln::mat3x4` {#structkln_1_1mat3x4}

3x4 column-major matrix (used for converting rotors/motors to matrix form to upload to shaders). Note that the storage requirement is identical to a column major [mat4x4](../../api/kln_mat4x4#structkln_1_1mat4x4) due to the SIMD representation.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public __m128 ` [`cols`](#structkln_1_1mat3x4_1ae217bae8c138f689d810b6f3b5792298) | 
`public float ` [`data`](#structkln_1_1mat3x4_1aa1d1afe15f3de970e020b325b8a34352) | 
`public union kln::mat3x4::@0 ` [`@1`](#structkln_1_1mat3x4_1ad712ecf0935631018aa4b43bdf823046) | 
`public __m128 KLN_VEC_CALL ` [`operator()`](#structkln_1_1mat3x4_1aec2ffe495ad2078179282c942c8b6e54)`(__m128 const & xyzw) const noexcept`  | Apply the linear transformation represented by this matrix to a point packed with the layout (x, y, z, 1.f)

### Members

#### __m128  [cols](#structkln_1_1mat3x4_1ae217bae8c138f689d810b6f3b5792298) {#structkln_1_1mat3x4_1ae217bae8c138f689d810b6f3b5792298}

#### float  [data](#structkln_1_1mat3x4_1aa1d1afe15f3de970e020b325b8a34352) {#structkln_1_1mat3x4_1aa1d1afe15f3de970e020b325b8a34352}

#### union kln::mat3x4::@0  [@1](#structkln_1_1mat3x4_1ad712ecf0935631018aa4b43bdf823046) {#structkln_1_1mat3x4_1ad712ecf0935631018aa4b43bdf823046}

#### __m128 KLN_VEC_CALL  [operator()](#structkln_1_1mat3x4_1aec2ffe495ad2078179282c942c8b6e54)(__m128 const & xyzw) const noexcept  {#structkln_1_1mat3x4_1aec2ffe495ad2078179282c942c8b6e54}

Apply the linear transformation represented by this matrix to a point packed with the layout (x, y, z, 1.f)

