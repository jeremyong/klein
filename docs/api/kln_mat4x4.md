## struct `kln::mat4x4` {#structkln_1_1mat4x4}

4x4 column-major matrix (used for converting rotors/motors to matrix form to upload to shaders).

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public __m128 ` [`cols`](#structkln_1_1mat4x4_1a3798edf63f7687c50c6aaf6f244877f5) | 
`public float ` [`data`](#structkln_1_1mat4x4_1a435faa5258c42d877bc0a5376d9f42cb) | 
`public union kln::mat4x4::@2 ` [`@3`](#structkln_1_1mat4x4_1a86acb74da8e8723910e63b3b739fa0f6) | 
`public __m128 KLN_VEC_CALL ` [`operator()`](#structkln_1_1mat4x4_1affa785d91804a64f48ebb0922179f24f)`(__m128 const & xyzw) const noexcept`  | Apply the linear transformation represented by this matrix to a point packed with the layout (x, y, z, 1.f)

### Members

#### __m128  [cols](#structkln_1_1mat4x4_1a3798edf63f7687c50c6aaf6f244877f5) {#structkln_1_1mat4x4_1a3798edf63f7687c50c6aaf6f244877f5}

#### float  [data](#structkln_1_1mat4x4_1a435faa5258c42d877bc0a5376d9f42cb) {#structkln_1_1mat4x4_1a435faa5258c42d877bc0a5376d9f42cb}

#### union kln::mat4x4::@2  [@3](#structkln_1_1mat4x4_1a86acb74da8e8723910e63b3b739fa0f6) {#structkln_1_1mat4x4_1a86acb74da8e8723910e63b3b739fa0f6}

#### __m128 KLN_VEC_CALL  [operator()](#structkln_1_1mat4x4_1affa785d91804a64f48ebb0922179f24f)(__m128 const & xyzw) const noexcept  {#structkln_1_1mat4x4_1affa785d91804a64f48ebb0922179f24f}

Apply the linear transformation represented by this matrix to a point packed with the layout (x, y, z, 1.f)

