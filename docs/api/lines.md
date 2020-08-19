## group `lines` {#group__lines}

Klein provides three line classes: "line", "branch", and "ideal_line". The line class represents a full six-coordinate bivector. The branch contains three non-degenerate components (aka, a line through the origin). The ideal line represents the line at infinity. When the line is created as a meet of two planes or join of two points (or carefully selected Plücker coordinates), it will be a Euclidean line (factorizable as the meet of two vectors).

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`ideal_line`](#group__lines_1ga62ef2297496614693083466f12635558)`() = default`             | 
`public  ` [`ideal_line`](#group__lines_1ga23cf4cb2763929db4f63dabadc1b9b32)`(float a,float b,float c) noexcept`             | 
`public  ` [`ideal_line`](#group__lines_1ga0734f86c43d547402c7d06d4eddb0691)`(__m128 xmm) noexcept`             | 
`public float ` [`squared_ideal_norm`](#group__lines_1ga4da377f9f9687a69e0cc1c84b936d53e)`() noexcept`             | 
`public float ` [`ideal_norm`](#group__lines_1gac38415e4e709ce83f215bfbbc6fa43a0)`() noexcept`             | 
`public ideal_line &KLN_VEC_CALL ` [`operator+=`](#group__lines_1ga6cd29f5c0d762ba34140adfb11e89d4c)`(ideal_line b) noexcept`             | Ideal line addition.
`public ideal_line &KLN_VEC_CALL ` [`operator-=`](#group__lines_1ga716f3c3a2bab34ea147157a129b259d0)`(ideal_line b) noexcept`             | Ideal line subtraction.
`public ideal_line & ` [`operator*=`](#group__lines_1ga50c085e141902ec94366bedfc5eb1993)`(float s) noexcept`             | Ideal line uniform scale.
`public ideal_line & ` [`operator*=`](#group__lines_1ga848437f19a14e0e0f946420b388066c2)`(int s) noexcept`             | Ideal line uniform scale.
`public ideal_line & ` [`operator/=`](#group__lines_1gad5022268754a921e8a91b22745da62fe)`(float s) noexcept`             | Ideal line uniform inverse scale.
`public ideal_line & ` [`operator/=`](#group__lines_1ga6540e3a798f002b7add9bc83fad74b09)`(int s) noexcept`             | Ideal line uniform inverse scale.
`public float ` [`e01`](#group__lines_1ga9209dc293ba4828ee9401471a2c39416)`() const noexcept`             | 
`public float ` [`e10`](#group__lines_1ga630a786b6a720571df80ce07be2b480d)`() const noexcept`             | 
`public float ` [`e02`](#group__lines_1ga64252faa6b55014eb29f1b0b0756c412)`() const noexcept`             | 
`public float ` [`e20`](#group__lines_1ga895a9f40d184bc766580cd4f937d9653)`() const noexcept`             | 
`public float ` [`e03`](#group__lines_1gad7926824f65759c7757206a16c955494)`() const noexcept`             | 
`public float ` [`e30`](#group__lines_1gaf9a7c9717ca8bca47567bc2eb9cbdf5e)`() const noexcept`             | 
`public ideal_line KLN_VEC_CALL ` [`operator+`](#group__lines_1gaf20ec975ef8d272dec782a21e92ad292)`(ideal_line a,ideal_line b) noexcept`             | Ideal line addition.
`public ideal_line KLN_VEC_CALL ` [`operator-`](#group__lines_1gae3e8dad43c2e6da933169175481b8807)`(ideal_line a,ideal_line b) noexcept`             | Ideal line subtraction.
`public ideal_line KLN_VEC_CALL ` [`operator*`](#group__lines_1ga8c687777271cee937c066f86cf8fc13e)`(ideal_line l,float s) noexcept`             | Ideal line uniform scale.
`public ideal_line KLN_VEC_CALL ` [`operator*`](#group__lines_1ga585458c330e0b6d6e3725aeb6d1f1711)`(ideal_line l,int s) noexcept`             | Ideal line uniform scale.
`public ideal_line KLN_VEC_CALL ` [`operator*`](#group__lines_1ga45fa818b3742c77e0a81fa35419e5a1d)`(float s,ideal_line l) noexcept`             | Ideal line uniform scale.
`public ideal_line KLN_VEC_CALL ` [`operator*`](#group__lines_1ga1c749bb69e95b736eb7ccc14b198ff41)`(int s,ideal_line l) noexcept`             | Ideal line uniform scale.
`public ideal_line KLN_VEC_CALL ` [`operator/`](#group__lines_1gad4c128535f9e5c60830442b18e62c419)`(ideal_line l,float s) noexcept`             | Ideal line uniform inverse scale.
`public ideal_line KLN_VEC_CALL ` [`operator/`](#group__lines_1ga600666bf5950f2a58c1d6d0aaefa41f3)`(ideal_line l,int s) noexcept`             | 
`public ideal_line KLN_VEC_CALL ` [`operator-`](#group__lines_1ga3d10cab9e9f55da1b0aea1f95697854f)`(ideal_line l) noexcept`             | Unary minus.
`public ideal_line KLN_VEC_CALL ` [`operator~`](#group__lines_1ga40e609b90210191b544d61d64032db7c)`(ideal_line l) noexcept`             | Reversion operator.
`public  ` [`branch`](#group__lines_1gac0b6196328f798a024d116b0052dc933)`() = default`             | 
`public  ` [`branch`](#group__lines_1ga85e647f4c92a2dd6896c5afd849d00a5)`(float a,float b,float c) noexcept`             | Construct the branch as the following multivector:
`public  ` [`branch`](#group__lines_1ga919bf9527b955fe1d58188edfe5aa802)`(__m128 xmm) noexcept`             | 
`public float ` [`squared_norm`](#group__lines_1ga0c6c16090b660c63df26aacf985c6f0c)`() noexcept`             | If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
`public float ` [`norm`](#group__lines_1ga6174cbd24d0189e3f5f9b893d63f5086)`() noexcept`             | Returns the square root of the quantity produced by `squared_norm` .
`public void ` [`normalize`](#group__lines_1ga4d9e87ff79bba150183642ac82404d13)`() noexcept`             | 
`public branch ` [`normalized`](#group__lines_1ga9d8961eee2687dd2b0ec3626193a0849)`() const noexcept`             | 
`public void ` [`invert`](#group__lines_1ga1979e6270f96d0fdab20e96f2207c1fa)`() noexcept`             | 
`public branch ` [`inverse`](#group__lines_1ga73cc09b7435bf131f8497a179dff059b)`() const noexcept`             | 
`public branch &KLN_VEC_CALL ` [`operator+=`](#group__lines_1gaeb5c16ed0187ff38df6c685529bb90c2)`(branch b) noexcept`             | Branch addition.
`public branch &KLN_VEC_CALL ` [`operator-=`](#group__lines_1ga69f66d6b2736f2fdaa02b45e72b1ba2f)`(branch b) noexcept`             | Branch subtraction.
`public branch & ` [`operator*=`](#group__lines_1ga174b924bea5109230431bce2ec996d77)`(float s) noexcept`             | Branch uniform scale.
`public branch & ` [`operator*=`](#group__lines_1gaf522a7fcce5ccd8ec64dd519b1355945)`(int s) noexcept`             | Branch uniform scale.
`public branch & ` [`operator/=`](#group__lines_1ga0059f1b65a43b001a072cb6e2e7c0702)`(float s) noexcept`             | Branch uniform inverse scale.
`public branch & ` [`operator/=`](#group__lines_1gac2d5f7065b967c378f52e192b5cda886)`(int s) noexcept`             | Branch uniform inverse scale.
`public float ` [`e12`](#group__lines_1gaf242b6c3e610d5a328dd251dfa8f47d0)`() const noexcept`             | 
`public float ` [`e21`](#group__lines_1ga7523c736e05eea04cd848201b0a93506)`() const noexcept`             | 
`public float ` [`z`](#group__lines_1ga9eebc3c6c95cec91949528d6ce064169)`() const noexcept`             | 
`public float ` [`e31`](#group__lines_1gac71e905e0f2758d0a6fa2242a135a568)`() const noexcept`             | 
`public float ` [`e13`](#group__lines_1gaa00e179436a14b16c88dae12a42792c2)`() const noexcept`             | 
`public float ` [`y`](#group__lines_1ga6093486d459bb08789ba50998e499794)`() const noexcept`             | 
`public float ` [`e23`](#group__lines_1ga7af485388456f1d35f6d25b493e3c466)`() const noexcept`             | 
`public float ` [`e32`](#group__lines_1gaffda6cbc92f913c96c8c9697c7f498a7)`() const noexcept`             | 
`public float ` [`x`](#group__lines_1ga639819fb843ea77e0cd153c370425267)`() const noexcept`             | 
`public branch KLN_VEC_CALL ` [`operator+`](#group__lines_1ga806e374cc4281cfc3eecec93d85a31fa)`(branch a,branch b) noexcept`             | Branch addition.
`public branch KLN_VEC_CALL ` [`operator-`](#group__lines_1ga2bad4a299ed2bcb5fb8532af40608e3d)`(branch a,branch b) noexcept`             | Branch subtraction.
`public branch KLN_VEC_CALL ` [`operator*`](#group__lines_1ga6f0f933a374ea30980fa71cc222fbdf1)`(branch b,float s) noexcept`             | Branch uniform scale.
`public branch KLN_VEC_CALL ` [`operator*`](#group__lines_1ga06f26bbb23a3ac8bf2da68d6d86cb9a0)`(branch b,int s) noexcept`             | Branch uniform scale.
`public branch KLN_VEC_CALL ` [`operator*`](#group__lines_1gafcb9d3b2717d1fdf3591c06894a285a2)`(float s,branch b) noexcept`             | Branch uniform scale.
`public branch KLN_VEC_CALL ` [`operator*`](#group__lines_1gaacf02b8f4c3af4e74eb6a09eb849cdfa)`(int s,branch b) noexcept`             | Branch uniform scale.
`public branch KLN_VEC_CALL ` [`operator/`](#group__lines_1ga029c94290f7cec1095460b3ca72fdb5c)`(branch b,float s) noexcept`             | Branch uniform inverse scale.
`public branch KLN_VEC_CALL ` [`operator/`](#group__lines_1ga749e37e9a3b976563ac06098c5011bf6)`(branch b,int s) noexcept`             | Branch uniform inverse scale.
`public branch KLN_VEC_CALL ` [`operator-`](#group__lines_1ga1445656708214b75860bc4c21dd92eac)`(branch b) noexcept`             | Unary minus.
`public branch KLN_VEC_CALL ` [`operator~`](#group__lines_1gaad8d9b139430ae9be3c575741ee82d6e)`(branch b) noexcept`             | Reversion operator.
`public  ` [`line`](#group__lines_1gaf274662f18385ec8065a083d235cc63e)`() = default`             | 
`public  ` [`line`](#group__lines_1ga3a7b1cdde6811a23a30cd5d4082ee5d7)`(float a,float b,float c,float d,float e,float f) noexcept`             | A line is specifed by 6 coordinates which correspond to the line's [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates). The coordinates specified in this way correspond to the following multivector:
`public  ` [`line`](#group__lines_1ga185af75e75e036164d3c1754da405737)`(__m128 xmm1,__m128 xmm2) noexcept`             | 
`public  ` [`line`](#group__lines_1gaddbd98af6bc9a738816347a15a83c276)`(ideal_line other) noexcept`             | 
`public  ` [`line`](#group__lines_1gae8e557447c170f2cbb3004b6d9945a9e)`(branch other) noexcept`             | 
`public float ` [`norm`](#group__lines_1gad388b8d134c0c22b1f82026277e39c22)`() noexcept`             | Returns the square root of the quantity produced by `squared_norm` .
`public float ` [`squared_norm`](#group__lines_1ga941c27dc8594f947ecf718160ebb084b)`() noexcept`             | If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
`public void ` [`normalize`](#group__lines_1ga1bf22b022eadfaf1e9f9179f346a4cd3)`() noexcept`             | Normalize a line such that $\ell^2 = -1$.
`public line ` [`normalized`](#group__lines_1ga276e9de782855e6c32560923dce491c4)`() const noexcept`             | Return a normalized copy of this line.
`public void ` [`invert`](#group__lines_1ga803c6bc20ae199f78a92419521366d2e)`() noexcept`             | 
`public line ` [`inverse`](#group__lines_1gac196dc5ee3591a2c302d3d78cd7abcd8)`() const noexcept`             | 
`public bool KLN_VEC_CALL ` [`operator==`](#group__lines_1gae443bd972f232ca9c17924283ab210c6)`(line other) const noexcept`             | Bitwise comparison.
`public bool KLN_VEC_CALL ` [`approx_eq`](#group__lines_1ga1b70abc509a2e60dbccb3131acd0801e)`(line other,float epsilon) const noexcept`             | 
`public line &KLN_VEC_CALL ` [`operator+=`](#group__lines_1ga3189260b7a1b0b6cf1f09a5b1b9bb8f3)`(line b) noexcept`             | Line addition.
`public line &KLN_VEC_CALL ` [`operator-=`](#group__lines_1ga1ab6e11021c616adfb35f5b11e478447)`(line b) noexcept`             | Line subtraction.
`public line & ` [`operator*=`](#group__lines_1ga64128e5413f0dd3e31808c6dae6aaad6)`(float s) noexcept`             | Line uniform scale.
`public line & ` [`operator*=`](#group__lines_1gabf0b448a99eda4e48f5b14c998dfbfbc)`(int s) noexcept`             | Line uniform scale.
`public line & ` [`operator/=`](#group__lines_1gab8d592169b9ed4abc4932a670d98131c)`(float s) noexcept`             | Line uniform inverse scale.
`public line & ` [`operator/=`](#group__lines_1ga23fdb26f06a4e172aec588b2034e56af)`(int s) noexcept`             | Line uniform inverse scale.
`public float ` [`e12`](#group__lines_1ga1362bf5e4fbf12c0a1fadeaa4cba905a)`() const noexcept`             | 
`public float ` [`e21`](#group__lines_1gaed1b130b5124643dfe1baf82ef43a091)`() const noexcept`             | 
`public float ` [`e31`](#group__lines_1gaeed171a99dbd03a54aaeeb4297a5f7d4)`() const noexcept`             | 
`public float ` [`e13`](#group__lines_1ga49c1718902c977c0d04a9aae046d97d5)`() const noexcept`             | 
`public float ` [`e23`](#group__lines_1ga637c8b7fa555e5dd30b0faadd88d0095)`() const noexcept`             | 
`public float ` [`e32`](#group__lines_1gaa150f5a6ee68b810f27f9624496face0)`() const noexcept`             | 
`public float ` [`e01`](#group__lines_1gac29f9783375c336ab2d3fb67a3431f07)`() const noexcept`             | 
`public float ` [`e10`](#group__lines_1ga7d163f4afca8fd89a796056c909245d1)`() const noexcept`             | 
`public float ` [`e02`](#group__lines_1gaa38fe9ae6e00bc4d595713c01ac1dd9f)`() const noexcept`             | 
`public float ` [`e20`](#group__lines_1ga4f37f6f38b720170d3b41ecc33c1cef9)`() const noexcept`             | 
`public float ` [`e03`](#group__lines_1gacd1e4c54ab209259cbd3c3042f286580)`() const noexcept`             | 
`public float ` [`e30`](#group__lines_1gaa75f3c527da3e76fba0f63defd1e822d)`() const noexcept`             | 
`public line KLN_VEC_CALL ` [`operator+`](#group__lines_1ga0a83f2a48198edd9507f5bbd4c9b30db)`(line a,line b) noexcept`             | Line addition.
`public line KLN_VEC_CALL ` [`operator-`](#group__lines_1gadb1e4f4b039a7b4876f5b594f31a3c18)`(line a,line b) noexcept`             | Line subtraction.
`public line KLN_VEC_CALL ` [`operator*`](#group__lines_1ga2ab242c8429056ce8a0eaff272d58055)`(line l,float s) noexcept`             | Line uniform scale.
`public line KLN_VEC_CALL ` [`operator*`](#group__lines_1gaeb3211aaaffb0c67796cd16fcc9fdfbb)`(line l,int s) noexcept`             | Line uniform scale.
`public line KLN_VEC_CALL ` [`operator*`](#group__lines_1gafc0250185f6abbab4af1dfc7ddd7d82f)`(float s,line l) noexcept`             | Line uniform scale.
`public line KLN_VEC_CALL ` [`operator*`](#group__lines_1ga8cb888db657b2113caea92ab8220594c)`(int s,line l) noexcept`             | Line uniform scale.
`public line KLN_VEC_CALL ` [`operator/`](#group__lines_1gafb3d9b8897b0af53ecb7e20887be0485)`(line r,float s) noexcept`             | Line uniform inverse scale.
`public line KLN_VEC_CALL ` [`operator/`](#group__lines_1gae8be4741283b0730feb08cdf697de2b1)`(line r,int s) noexcept`             | Line uniform inverse scale.
`public line KLN_VEC_CALL ` [`operator-`](#group__lines_1ga17f373e90ac62d4218dae72f9f2099d3)`(line l) noexcept`             | Unary minus.
`public line KLN_VEC_CALL ` [`operator~`](#group__lines_1gadb187ac167c98d721c8eea5eed2f0120)`(line l) noexcept`             | Reversion operator.

### Members

####   [ideal_line](#group__lines_1ga62ef2297496614693083466f12635558)() = default  {#group__lines_1ga62ef2297496614693083466f12635558}

####   [ideal_line](#group__lines_1ga23cf4cb2763929db4f63dabadc1b9b32)(float a,float b,float c) noexcept  {#group__lines_1ga23cf4cb2763929db4f63dabadc1b9b32}

####   [ideal_line](#group__lines_1ga0734f86c43d547402c7d06d4eddb0691)(__m128 xmm) noexcept  {#group__lines_1ga0734f86c43d547402c7d06d4eddb0691}

#### float  [squared_ideal_norm](#group__lines_1ga4da377f9f9687a69e0cc1c84b936d53e)() noexcept  {#group__lines_1ga4da377f9f9687a69e0cc1c84b936d53e}

#### float  [ideal_norm](#group__lines_1gac38415e4e709ce83f215bfbbc6fa43a0)() noexcept  {#group__lines_1gac38415e4e709ce83f215bfbbc6fa43a0}

#### ideal_line &KLN_VEC_CALL  [operator+=](#group__lines_1ga6cd29f5c0d762ba34140adfb11e89d4c)(ideal_line b) noexcept  {#group__lines_1ga6cd29f5c0d762ba34140adfb11e89d4c}

Ideal line addition.

#### ideal_line &KLN_VEC_CALL  [operator-=](#group__lines_1ga716f3c3a2bab34ea147157a129b259d0)(ideal_line b) noexcept  {#group__lines_1ga716f3c3a2bab34ea147157a129b259d0}

Ideal line subtraction.

#### ideal_line &  [operator*=](#group__lines_1ga50c085e141902ec94366bedfc5eb1993)(float s) noexcept  {#group__lines_1ga50c085e141902ec94366bedfc5eb1993}

Ideal line uniform scale.

#### ideal_line &  [operator*=](#group__lines_1ga848437f19a14e0e0f946420b388066c2)(int s) noexcept  {#group__lines_1ga848437f19a14e0e0f946420b388066c2}

Ideal line uniform scale.

#### ideal_line &  [operator/=](#group__lines_1gad5022268754a921e8a91b22745da62fe)(float s) noexcept  {#group__lines_1gad5022268754a921e8a91b22745da62fe}

Ideal line uniform inverse scale.

#### ideal_line &  [operator/=](#group__lines_1ga6540e3a798f002b7add9bc83fad74b09)(int s) noexcept  {#group__lines_1ga6540e3a798f002b7add9bc83fad74b09}

Ideal line uniform inverse scale.

#### float  [e01](#group__lines_1ga9209dc293ba4828ee9401471a2c39416)() const noexcept  {#group__lines_1ga9209dc293ba4828ee9401471a2c39416}

#### float  [e10](#group__lines_1ga630a786b6a720571df80ce07be2b480d)() const noexcept  {#group__lines_1ga630a786b6a720571df80ce07be2b480d}

#### float  [e02](#group__lines_1ga64252faa6b55014eb29f1b0b0756c412)() const noexcept  {#group__lines_1ga64252faa6b55014eb29f1b0b0756c412}

#### float  [e20](#group__lines_1ga895a9f40d184bc766580cd4f937d9653)() const noexcept  {#group__lines_1ga895a9f40d184bc766580cd4f937d9653}

#### float  [e03](#group__lines_1gad7926824f65759c7757206a16c955494)() const noexcept  {#group__lines_1gad7926824f65759c7757206a16c955494}

#### float  [e30](#group__lines_1gaf9a7c9717ca8bca47567bc2eb9cbdf5e)() const noexcept  {#group__lines_1gaf9a7c9717ca8bca47567bc2eb9cbdf5e}

#### ideal_line KLN_VEC_CALL  [operator+](#group__lines_1gaf20ec975ef8d272dec782a21e92ad292)(ideal_line a,ideal_line b) noexcept  {#group__lines_1gaf20ec975ef8d272dec782a21e92ad292}

Ideal line addition.

#### ideal_line KLN_VEC_CALL  [operator-](#group__lines_1gae3e8dad43c2e6da933169175481b8807)(ideal_line a,ideal_line b) noexcept  {#group__lines_1gae3e8dad43c2e6da933169175481b8807}

Ideal line subtraction.

#### ideal_line KLN_VEC_CALL  [operator*](#group__lines_1ga8c687777271cee937c066f86cf8fc13e)(ideal_line l,float s) noexcept  {#group__lines_1ga8c687777271cee937c066f86cf8fc13e}

Ideal line uniform scale.

#### ideal_line KLN_VEC_CALL  [operator*](#group__lines_1ga585458c330e0b6d6e3725aeb6d1f1711)(ideal_line l,int s) noexcept  {#group__lines_1ga585458c330e0b6d6e3725aeb6d1f1711}

Ideal line uniform scale.

#### ideal_line KLN_VEC_CALL  [operator*](#group__lines_1ga45fa818b3742c77e0a81fa35419e5a1d)(float s,ideal_line l) noexcept  {#group__lines_1ga45fa818b3742c77e0a81fa35419e5a1d}

Ideal line uniform scale.

#### ideal_line KLN_VEC_CALL  [operator*](#group__lines_1ga1c749bb69e95b736eb7ccc14b198ff41)(int s,ideal_line l) noexcept  {#group__lines_1ga1c749bb69e95b736eb7ccc14b198ff41}

Ideal line uniform scale.

#### ideal_line KLN_VEC_CALL  [operator/](#group__lines_1gad4c128535f9e5c60830442b18e62c419)(ideal_line l,float s) noexcept  {#group__lines_1gad4c128535f9e5c60830442b18e62c419}

Ideal line uniform inverse scale.

#### ideal_line KLN_VEC_CALL  [operator/](#group__lines_1ga600666bf5950f2a58c1d6d0aaefa41f3)(ideal_line l,int s) noexcept  {#group__lines_1ga600666bf5950f2a58c1d6d0aaefa41f3}

#### ideal_line KLN_VEC_CALL  [operator-](#group__lines_1ga3d10cab9e9f55da1b0aea1f95697854f)(ideal_line l) noexcept  {#group__lines_1ga3d10cab9e9f55da1b0aea1f95697854f}

Unary minus.

#### ideal_line KLN_VEC_CALL  [operator~](#group__lines_1ga40e609b90210191b544d61d64032db7c)(ideal_line l) noexcept  {#group__lines_1ga40e609b90210191b544d61d64032db7c}

Reversion operator.

####   [branch](#group__lines_1gac0b6196328f798a024d116b0052dc933)() = default  {#group__lines_1gac0b6196328f798a024d116b0052dc933}

####   [branch](#group__lines_1ga85e647f4c92a2dd6896c5afd849d00a5)(float a,float b,float c) noexcept  {#group__lines_1ga85e647f4c92a2dd6896c5afd849d00a5}

Construct the branch as the following multivector:

$$a \mathbf{e}_{23} + b\mathbf{e}_{31} + c\mathbf{e}_{12}$$

To convince yourself this is a line through the origin, remember that such a line can be generated using the geometric product of two planes through the origin.

####   [branch](#group__lines_1ga919bf9527b955fe1d58188edfe5aa802)(__m128 xmm) noexcept  {#group__lines_1ga919bf9527b955fe1d58188edfe5aa802}

#### float  [squared_norm](#group__lines_1ga0c6c16090b660c63df26aacf985c6f0c)() noexcept  {#group__lines_1ga0c6c16090b660c63df26aacf985c6f0c}

If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.

#### float  [norm](#group__lines_1ga6174cbd24d0189e3f5f9b893d63f5086)() noexcept  {#group__lines_1ga6174cbd24d0189e3f5f9b893d63f5086}

Returns the square root of the quantity produced by `squared_norm` .

#### void  [normalize](#group__lines_1ga4d9e87ff79bba150183642ac82404d13)() noexcept  {#group__lines_1ga4d9e87ff79bba150183642ac82404d13}

#### branch  [normalized](#group__lines_1ga9d8961eee2687dd2b0ec3626193a0849)() const noexcept  {#group__lines_1ga9d8961eee2687dd2b0ec3626193a0849}

#### void  [invert](#group__lines_1ga1979e6270f96d0fdab20e96f2207c1fa)() noexcept  {#group__lines_1ga1979e6270f96d0fdab20e96f2207c1fa}

#### branch  [inverse](#group__lines_1ga73cc09b7435bf131f8497a179dff059b)() const noexcept  {#group__lines_1ga73cc09b7435bf131f8497a179dff059b}

#### branch &KLN_VEC_CALL  [operator+=](#group__lines_1gaeb5c16ed0187ff38df6c685529bb90c2)(branch b) noexcept  {#group__lines_1gaeb5c16ed0187ff38df6c685529bb90c2}

Branch addition.

#### branch &KLN_VEC_CALL  [operator-=](#group__lines_1ga69f66d6b2736f2fdaa02b45e72b1ba2f)(branch b) noexcept  {#group__lines_1ga69f66d6b2736f2fdaa02b45e72b1ba2f}

Branch subtraction.

#### branch &  [operator*=](#group__lines_1ga174b924bea5109230431bce2ec996d77)(float s) noexcept  {#group__lines_1ga174b924bea5109230431bce2ec996d77}

Branch uniform scale.

#### branch &  [operator*=](#group__lines_1gaf522a7fcce5ccd8ec64dd519b1355945)(int s) noexcept  {#group__lines_1gaf522a7fcce5ccd8ec64dd519b1355945}

Branch uniform scale.

#### branch &  [operator/=](#group__lines_1ga0059f1b65a43b001a072cb6e2e7c0702)(float s) noexcept  {#group__lines_1ga0059f1b65a43b001a072cb6e2e7c0702}

Branch uniform inverse scale.

#### branch &  [operator/=](#group__lines_1gac2d5f7065b967c378f52e192b5cda886)(int s) noexcept  {#group__lines_1gac2d5f7065b967c378f52e192b5cda886}

Branch uniform inverse scale.

#### float  [e12](#group__lines_1gaf242b6c3e610d5a328dd251dfa8f47d0)() const noexcept  {#group__lines_1gaf242b6c3e610d5a328dd251dfa8f47d0}

#### float  [e21](#group__lines_1ga7523c736e05eea04cd848201b0a93506)() const noexcept  {#group__lines_1ga7523c736e05eea04cd848201b0a93506}

#### float  [z](#group__lines_1ga9eebc3c6c95cec91949528d6ce064169)() const noexcept  {#group__lines_1ga9eebc3c6c95cec91949528d6ce064169}

#### float  [e31](#group__lines_1gac71e905e0f2758d0a6fa2242a135a568)() const noexcept  {#group__lines_1gac71e905e0f2758d0a6fa2242a135a568}

#### float  [e13](#group__lines_1gaa00e179436a14b16c88dae12a42792c2)() const noexcept  {#group__lines_1gaa00e179436a14b16c88dae12a42792c2}

#### float  [y](#group__lines_1ga6093486d459bb08789ba50998e499794)() const noexcept  {#group__lines_1ga6093486d459bb08789ba50998e499794}

#### float  [e23](#group__lines_1ga7af485388456f1d35f6d25b493e3c466)() const noexcept  {#group__lines_1ga7af485388456f1d35f6d25b493e3c466}

#### float  [e32](#group__lines_1gaffda6cbc92f913c96c8c9697c7f498a7)() const noexcept  {#group__lines_1gaffda6cbc92f913c96c8c9697c7f498a7}

#### float  [x](#group__lines_1ga639819fb843ea77e0cd153c370425267)() const noexcept  {#group__lines_1ga639819fb843ea77e0cd153c370425267}

#### branch KLN_VEC_CALL  [operator+](#group__lines_1ga806e374cc4281cfc3eecec93d85a31fa)(branch a,branch b) noexcept  {#group__lines_1ga806e374cc4281cfc3eecec93d85a31fa}

Branch addition.

#### branch KLN_VEC_CALL  [operator-](#group__lines_1ga2bad4a299ed2bcb5fb8532af40608e3d)(branch a,branch b) noexcept  {#group__lines_1ga2bad4a299ed2bcb5fb8532af40608e3d}

Branch subtraction.

#### branch KLN_VEC_CALL  [operator*](#group__lines_1ga6f0f933a374ea30980fa71cc222fbdf1)(branch b,float s) noexcept  {#group__lines_1ga6f0f933a374ea30980fa71cc222fbdf1}

Branch uniform scale.

#### branch KLN_VEC_CALL  [operator*](#group__lines_1ga06f26bbb23a3ac8bf2da68d6d86cb9a0)(branch b,int s) noexcept  {#group__lines_1ga06f26bbb23a3ac8bf2da68d6d86cb9a0}

Branch uniform scale.

#### branch KLN_VEC_CALL  [operator*](#group__lines_1gafcb9d3b2717d1fdf3591c06894a285a2)(float s,branch b) noexcept  {#group__lines_1gafcb9d3b2717d1fdf3591c06894a285a2}

Branch uniform scale.

#### branch KLN_VEC_CALL  [operator*](#group__lines_1gaacf02b8f4c3af4e74eb6a09eb849cdfa)(int s,branch b) noexcept  {#group__lines_1gaacf02b8f4c3af4e74eb6a09eb849cdfa}

Branch uniform scale.

#### branch KLN_VEC_CALL  [operator/](#group__lines_1ga029c94290f7cec1095460b3ca72fdb5c)(branch b,float s) noexcept  {#group__lines_1ga029c94290f7cec1095460b3ca72fdb5c}

Branch uniform inverse scale.

#### branch KLN_VEC_CALL  [operator/](#group__lines_1ga749e37e9a3b976563ac06098c5011bf6)(branch b,int s) noexcept  {#group__lines_1ga749e37e9a3b976563ac06098c5011bf6}

Branch uniform inverse scale.

#### branch KLN_VEC_CALL  [operator-](#group__lines_1ga1445656708214b75860bc4c21dd92eac)(branch b) noexcept  {#group__lines_1ga1445656708214b75860bc4c21dd92eac}

Unary minus.

#### branch KLN_VEC_CALL  [operator~](#group__lines_1gaad8d9b139430ae9be3c575741ee82d6e)(branch b) noexcept  {#group__lines_1gaad8d9b139430ae9be3c575741ee82d6e}

Reversion operator.

####   [line](#group__lines_1gaf274662f18385ec8065a083d235cc63e)() = default  {#group__lines_1gaf274662f18385ec8065a083d235cc63e}

####   [line](#group__lines_1ga3a7b1cdde6811a23a30cd5d4082ee5d7)(float a,float b,float c,float d,float e,float f) noexcept  {#group__lines_1ga3a7b1cdde6811a23a30cd5d4082ee5d7}

A line is specifed by 6 coordinates which correspond to the line's [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates). The coordinates specified in this way correspond to the following multivector:

$$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03} +\ d\mathbf{e}_{23} + e\mathbf{e}_{31} + f\mathbf{e}_{12}$$

####   [line](#group__lines_1ga185af75e75e036164d3c1754da405737)(__m128 xmm1,__m128 xmm2) noexcept  {#group__lines_1ga185af75e75e036164d3c1754da405737}

####   [line](#group__lines_1gaddbd98af6bc9a738816347a15a83c276)(ideal_line other) noexcept  {#group__lines_1gaddbd98af6bc9a738816347a15a83c276}

####   [line](#group__lines_1gae8e557447c170f2cbb3004b6d9945a9e)(branch other) noexcept  {#group__lines_1gae8e557447c170f2cbb3004b6d9945a9e}

#### float  [norm](#group__lines_1gad388b8d134c0c22b1f82026277e39c22)() noexcept  {#group__lines_1gad388b8d134c0c22b1f82026277e39c22}

Returns the square root of the quantity produced by `squared_norm` .

#### float  [squared_norm](#group__lines_1ga941c27dc8594f947ecf718160ebb084b)() noexcept  {#group__lines_1ga941c27dc8594f947ecf718160ebb084b}

If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.

#### void  [normalize](#group__lines_1ga1bf22b022eadfaf1e9f9179f346a4cd3)() noexcept  {#group__lines_1ga1bf22b022eadfaf1e9f9179f346a4cd3}

Normalize a line such that $\ell^2 = -1$.

#### line  [normalized](#group__lines_1ga276e9de782855e6c32560923dce491c4)() const noexcept  {#group__lines_1ga276e9de782855e6c32560923dce491c4}

Return a normalized copy of this line.

#### void  [invert](#group__lines_1ga803c6bc20ae199f78a92419521366d2e)() noexcept  {#group__lines_1ga803c6bc20ae199f78a92419521366d2e}

#### line  [inverse](#group__lines_1gac196dc5ee3591a2c302d3d78cd7abcd8)() const noexcept  {#group__lines_1gac196dc5ee3591a2c302d3d78cd7abcd8}

#### bool KLN_VEC_CALL  [operator==](#group__lines_1gae443bd972f232ca9c17924283ab210c6)(line other) const noexcept  {#group__lines_1gae443bd972f232ca9c17924283ab210c6}

Bitwise comparison.

#### bool KLN_VEC_CALL  [approx_eq](#group__lines_1ga1b70abc509a2e60dbccb3131acd0801e)(line other,float epsilon) const noexcept  {#group__lines_1ga1b70abc509a2e60dbccb3131acd0801e}

#### line &KLN_VEC_CALL  [operator+=](#group__lines_1ga3189260b7a1b0b6cf1f09a5b1b9bb8f3)(line b) noexcept  {#group__lines_1ga3189260b7a1b0b6cf1f09a5b1b9bb8f3}

Line addition.

#### line &KLN_VEC_CALL  [operator-=](#group__lines_1ga1ab6e11021c616adfb35f5b11e478447)(line b) noexcept  {#group__lines_1ga1ab6e11021c616adfb35f5b11e478447}

Line subtraction.

#### line &  [operator*=](#group__lines_1ga64128e5413f0dd3e31808c6dae6aaad6)(float s) noexcept  {#group__lines_1ga64128e5413f0dd3e31808c6dae6aaad6}

Line uniform scale.

#### line &  [operator*=](#group__lines_1gabf0b448a99eda4e48f5b14c998dfbfbc)(int s) noexcept  {#group__lines_1gabf0b448a99eda4e48f5b14c998dfbfbc}

Line uniform scale.

#### line &  [operator/=](#group__lines_1gab8d592169b9ed4abc4932a670d98131c)(float s) noexcept  {#group__lines_1gab8d592169b9ed4abc4932a670d98131c}

Line uniform inverse scale.

#### line &  [operator/=](#group__lines_1ga23fdb26f06a4e172aec588b2034e56af)(int s) noexcept  {#group__lines_1ga23fdb26f06a4e172aec588b2034e56af}

Line uniform inverse scale.

#### float  [e12](#group__lines_1ga1362bf5e4fbf12c0a1fadeaa4cba905a)() const noexcept  {#group__lines_1ga1362bf5e4fbf12c0a1fadeaa4cba905a}

#### float  [e21](#group__lines_1gaed1b130b5124643dfe1baf82ef43a091)() const noexcept  {#group__lines_1gaed1b130b5124643dfe1baf82ef43a091}

#### float  [e31](#group__lines_1gaeed171a99dbd03a54aaeeb4297a5f7d4)() const noexcept  {#group__lines_1gaeed171a99dbd03a54aaeeb4297a5f7d4}

#### float  [e13](#group__lines_1ga49c1718902c977c0d04a9aae046d97d5)() const noexcept  {#group__lines_1ga49c1718902c977c0d04a9aae046d97d5}

#### float  [e23](#group__lines_1ga637c8b7fa555e5dd30b0faadd88d0095)() const noexcept  {#group__lines_1ga637c8b7fa555e5dd30b0faadd88d0095}

#### float  [e32](#group__lines_1gaa150f5a6ee68b810f27f9624496face0)() const noexcept  {#group__lines_1gaa150f5a6ee68b810f27f9624496face0}

#### float  [e01](#group__lines_1gac29f9783375c336ab2d3fb67a3431f07)() const noexcept  {#group__lines_1gac29f9783375c336ab2d3fb67a3431f07}

#### float  [e10](#group__lines_1ga7d163f4afca8fd89a796056c909245d1)() const noexcept  {#group__lines_1ga7d163f4afca8fd89a796056c909245d1}

#### float  [e02](#group__lines_1gaa38fe9ae6e00bc4d595713c01ac1dd9f)() const noexcept  {#group__lines_1gaa38fe9ae6e00bc4d595713c01ac1dd9f}

#### float  [e20](#group__lines_1ga4f37f6f38b720170d3b41ecc33c1cef9)() const noexcept  {#group__lines_1ga4f37f6f38b720170d3b41ecc33c1cef9}

#### float  [e03](#group__lines_1gacd1e4c54ab209259cbd3c3042f286580)() const noexcept  {#group__lines_1gacd1e4c54ab209259cbd3c3042f286580}

#### float  [e30](#group__lines_1gaa75f3c527da3e76fba0f63defd1e822d)() const noexcept  {#group__lines_1gaa75f3c527da3e76fba0f63defd1e822d}

#### line KLN_VEC_CALL  [operator+](#group__lines_1ga0a83f2a48198edd9507f5bbd4c9b30db)(line a,line b) noexcept  {#group__lines_1ga0a83f2a48198edd9507f5bbd4c9b30db}

Line addition.

#### line KLN_VEC_CALL  [operator-](#group__lines_1gadb1e4f4b039a7b4876f5b594f31a3c18)(line a,line b) noexcept  {#group__lines_1gadb1e4f4b039a7b4876f5b594f31a3c18}

Line subtraction.

#### line KLN_VEC_CALL  [operator*](#group__lines_1ga2ab242c8429056ce8a0eaff272d58055)(line l,float s) noexcept  {#group__lines_1ga2ab242c8429056ce8a0eaff272d58055}

Line uniform scale.

#### line KLN_VEC_CALL  [operator*](#group__lines_1gaeb3211aaaffb0c67796cd16fcc9fdfbb)(line l,int s) noexcept  {#group__lines_1gaeb3211aaaffb0c67796cd16fcc9fdfbb}

Line uniform scale.

#### line KLN_VEC_CALL  [operator*](#group__lines_1gafc0250185f6abbab4af1dfc7ddd7d82f)(float s,line l) noexcept  {#group__lines_1gafc0250185f6abbab4af1dfc7ddd7d82f}

Line uniform scale.

#### line KLN_VEC_CALL  [operator*](#group__lines_1ga8cb888db657b2113caea92ab8220594c)(int s,line l) noexcept  {#group__lines_1ga8cb888db657b2113caea92ab8220594c}

Line uniform scale.

#### line KLN_VEC_CALL  [operator/](#group__lines_1gafb3d9b8897b0af53ecb7e20887be0485)(line r,float s) noexcept  {#group__lines_1gafb3d9b8897b0af53ecb7e20887be0485}

Line uniform inverse scale.

#### line KLN_VEC_CALL  [operator/](#group__lines_1gae8be4741283b0730feb08cdf697de2b1)(line r,int s) noexcept  {#group__lines_1gae8be4741283b0730feb08cdf697de2b1}

Line uniform inverse scale.

#### line KLN_VEC_CALL  [operator-](#group__lines_1ga17f373e90ac62d4218dae72f9f2099d3)(line l) noexcept  {#group__lines_1ga17f373e90ac62d4218dae72f9f2099d3}

Unary minus.

#### line KLN_VEC_CALL  [operator~](#group__lines_1gadb187ac167c98d721c8eea5eed2f0120)(line l) noexcept  {#group__lines_1gadb187ac167c98d721c8eea5eed2f0120}

Reversion operator.

