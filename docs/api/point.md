## group `point` {#group__point}

A point is represented as the multivector $x\mathbf{e}_{032} + y\mathbf{e}_{013} + z\mathbf{e}_{021} + \mathbf{e}_{123}$. The point has a trivector representation because it is the fixed point of 3 planar reflections (each of which is a grade-1 multivector). In practice, the coordinate mapping can be thought of as an implementation detail.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`point`](#group__point_1gaf5815698f91b6e3c0d1a4c6ee1584c2e)`() = default`             | 
`public  ` [`point`](#group__point_1gac37d4cefd1d57c3a7686420aee94bc5a)`(__m128 xmm) noexcept`             | 
`public  ` [`point`](#group__point_1gadc78c30fe71a140259dd7add02d36df8)`(float x,float y,float z) noexcept`             | Component-wise constructor (homogeneous coordinate is automatically initialized to 1)
`public void ` [`load`](#group__point_1ga805739dde6d772f5b228cce5b95ef13f)`(float * data) noexcept`             | Fast load from a pointer to an array of four floats with layout `(w, x, y, z)`  where `w`  occupies the lowest address in memory.
`public void ` [`normalize`](#group__point_1ga3d1ba8e0c47d25c5b5d124d9b5ef8e04)`() noexcept`             | Normalize this point (division is done via rcpps with an additional Newton-Raphson refinement).
`public point ` [`normalized`](#group__point_1ga8f4c5fa5342ffda6c73695b2fbfa0f9b)`() const noexcept`             | Return a normalized copy of this point.
`public void ` [`invert`](#group__point_1ga6ffcd424ab00bf033d241d55e901b209)`() noexcept`             | 
`public point ` [`inverse`](#group__point_1ga4abcf2a7bce6975617ada1a3be8bc47d)`() const noexcept`             | 
`public float ` [`x`](#group__point_1ga0c100888d1b7edc3fdb81f8b7c22feb1)`() const noexcept`             | 
`public float ` [`e032`](#group__point_1ga1a733ef19316e24dc74867e91c27d126)`() const noexcept`             | 
`public float ` [`y`](#group__point_1gae413703952e1a6e15b401d2620f6ae93)`() const noexcept`             | 
`public float ` [`e013`](#group__point_1ga22e2cd89dd1cc905fa2836e9a4e3cde8)`() const noexcept`             | 
`public float ` [`z`](#group__point_1gaff266ae56b86d0598a0373ea222c2bee)`() const noexcept`             | 
`public float ` [`e021`](#group__point_1ga5512ddec0c7a73b1f6509b6cd97f1da4)`() const noexcept`             | 
`public float ` [`w`](#group__point_1gadfa0b3fa1bc85799e2a3916725b573c1)`() const noexcept`             | The homogeneous coordinate `w`  is exactly $1$ when normalized.
`public float ` [`e123`](#group__point_1gaf2bb6211c7d2adaea7a128e8d2900bf3)`() const noexcept`             | 
`public point &KLN_VEC_CALL ` [`operator+=`](#group__point_1ga5249e834b0b88dc9db4a95c340c790d7)`(point b) noexcept`             | Point addition.
`public point &KLN_VEC_CALL ` [`operator-=`](#group__point_1gad19d2cb5801f3b5572487e85cda8a084)`(point b) noexcept`             | Point subtraction.
`public point & ` [`operator*=`](#group__point_1gac0d5012938591d0c765989fe0b100368)`(float s) noexcept`             | Point uniform scale.
`public point & ` [`operator*=`](#group__point_1ga036f220b5f049ad496fcee0a98477380)`(int s) noexcept`             | Point uniform scale.
`public point & ` [`operator/=`](#group__point_1ga1e02c8e04a37230a9f78c76c4390b199)`(float s) noexcept`             | Point uniform inverse scale.
`public point & ` [`operator/=`](#group__point_1gad37f2b9901bf72e2b8fc4d62ba7f99af)`(int s) noexcept`             | Point uniform inverse scale.
`public point KLN_VEC_CALL ` [`operator+`](#group__point_1ga7c772c35c230f28573611c707ec46243)`(point a,point b) noexcept`             | Point addition.
`public point KLN_VEC_CALL ` [`operator-`](#group__point_1ga893da0547e267d631fe79526f1c3d274)`(point a,point b) noexcept`             | Point subtraction.
`public point KLN_VEC_CALL ` [`operator*`](#group__point_1gadd07ab21ac8bf227aa0b7b56effda3ed)`(point p,float s) noexcept`             | Point uniform scale.
`public point KLN_VEC_CALL ` [`operator*`](#group__point_1ga18b3a2d1e891f46f9a59a5b13ab30797)`(float s,point p) noexcept`             | Point uniform scale.
`public point KLN_VEC_CALL ` [`operator*`](#group__point_1ga1e1b44a57e524d8d6eb2acce6e859f1b)`(point p,int s) noexcept`             | Point uniform scale.
`public point KLN_VEC_CALL ` [`operator*`](#group__point_1ga7033b360b0bc9476403ebe099ba86ea3)`(int s,point p) noexcept`             | Point uniform scale.
`public point KLN_VEC_CALL ` [`operator/`](#group__point_1ga98d52f70be04ecd1936acb684a7dd3a3)`(point p,float s) noexcept`             | Point uniform inverse scale.
`public point KLN_VEC_CALL ` [`operator/`](#group__point_1ga0ecf62635012f01c124f9294b4dd4a2e)`(point p,int s) noexcept`             | Point uniform inverse scale.
`public point KLN_VEC_CALL ` [`operator-`](#group__point_1ga7b18bf2b94b9e7d2e013eb710dbe11ac)`(point p) noexcept`             | Unary minus (leaves homogeneous coordinate untouched)
`public point KLN_VEC_CALL ` [`operator~`](#group__point_1ga5b6009037927bd8a00156237756f7566)`(point p) noexcept`             | Reversion operator.
`public  ` [`operator point`](#group__point_1gac078bf1318b763fe44d89abf77d3b3ef)`() const noexcept`             | On its own, the origin occupies no memory, but it can be casted as an entity at any point, at which point it is represented as $\mathbf{e}_{123}$.

### Members

####   [point](#group__point_1gaf5815698f91b6e3c0d1a4c6ee1584c2e)() = default  {#group__point_1gaf5815698f91b6e3c0d1a4c6ee1584c2e}

####   [point](#group__point_1gac37d4cefd1d57c3a7686420aee94bc5a)(__m128 xmm) noexcept  {#group__point_1gac37d4cefd1d57c3a7686420aee94bc5a}

####   [point](#group__point_1gadc78c30fe71a140259dd7add02d36df8)(float x,float y,float z) noexcept  {#group__point_1gadc78c30fe71a140259dd7add02d36df8}

Component-wise constructor (homogeneous coordinate is automatically initialized to 1)

#### void  [load](#group__point_1ga805739dde6d772f5b228cce5b95ef13f)(float * data) noexcept  {#group__point_1ga805739dde6d772f5b228cce5b95ef13f}

Fast load from a pointer to an array of four floats with layout `(w, x, y, z)`  where `w`  occupies the lowest address in memory.

!!! tip 
    This load operation is more efficient that modifying individual
    components back-to-back.
    

!!! danger 
    Unlike the component-wise constructor, the load here requires the
    homogeneous coordinate `w` to be supplied as well in the lowest
    address pointed to by `data`.

#### void  [normalize](#group__point_1ga3d1ba8e0c47d25c5b5d124d9b5ef8e04)() noexcept  {#group__point_1ga3d1ba8e0c47d25c5b5d124d9b5ef8e04}

Normalize this point (division is done via rcpps with an additional Newton-Raphson refinement).

#### point  [normalized](#group__point_1ga8f4c5fa5342ffda6c73695b2fbfa0f9b)() const noexcept  {#group__point_1ga8f4c5fa5342ffda6c73695b2fbfa0f9b}

Return a normalized copy of this point.

#### void  [invert](#group__point_1ga6ffcd424ab00bf033d241d55e901b209)() noexcept  {#group__point_1ga6ffcd424ab00bf033d241d55e901b209}

#### point  [inverse](#group__point_1ga4abcf2a7bce6975617ada1a3be8bc47d)() const noexcept  {#group__point_1ga4abcf2a7bce6975617ada1a3be8bc47d}

#### float  [x](#group__point_1ga0c100888d1b7edc3fdb81f8b7c22feb1)() const noexcept  {#group__point_1ga0c100888d1b7edc3fdb81f8b7c22feb1}

#### float  [e032](#group__point_1ga1a733ef19316e24dc74867e91c27d126)() const noexcept  {#group__point_1ga1a733ef19316e24dc74867e91c27d126}

#### float  [y](#group__point_1gae413703952e1a6e15b401d2620f6ae93)() const noexcept  {#group__point_1gae413703952e1a6e15b401d2620f6ae93}

#### float  [e013](#group__point_1ga22e2cd89dd1cc905fa2836e9a4e3cde8)() const noexcept  {#group__point_1ga22e2cd89dd1cc905fa2836e9a4e3cde8}

#### float  [z](#group__point_1gaff266ae56b86d0598a0373ea222c2bee)() const noexcept  {#group__point_1gaff266ae56b86d0598a0373ea222c2bee}

#### float  [e021](#group__point_1ga5512ddec0c7a73b1f6509b6cd97f1da4)() const noexcept  {#group__point_1ga5512ddec0c7a73b1f6509b6cd97f1da4}

#### float  [w](#group__point_1gadfa0b3fa1bc85799e2a3916725b573c1)() const noexcept  {#group__point_1gadfa0b3fa1bc85799e2a3916725b573c1}

The homogeneous coordinate `w`  is exactly $1$ when normalized.

#### float  [e123](#group__point_1gaf2bb6211c7d2adaea7a128e8d2900bf3)() const noexcept  {#group__point_1gaf2bb6211c7d2adaea7a128e8d2900bf3}

#### point &KLN_VEC_CALL  [operator+=](#group__point_1ga5249e834b0b88dc9db4a95c340c790d7)(point b) noexcept  {#group__point_1ga5249e834b0b88dc9db4a95c340c790d7}

Point addition.

#### point &KLN_VEC_CALL  [operator-=](#group__point_1gad19d2cb5801f3b5572487e85cda8a084)(point b) noexcept  {#group__point_1gad19d2cb5801f3b5572487e85cda8a084}

Point subtraction.

#### point &  [operator*=](#group__point_1gac0d5012938591d0c765989fe0b100368)(float s) noexcept  {#group__point_1gac0d5012938591d0c765989fe0b100368}

Point uniform scale.

#### point &  [operator*=](#group__point_1ga036f220b5f049ad496fcee0a98477380)(int s) noexcept  {#group__point_1ga036f220b5f049ad496fcee0a98477380}

Point uniform scale.

#### point &  [operator/=](#group__point_1ga1e02c8e04a37230a9f78c76c4390b199)(float s) noexcept  {#group__point_1ga1e02c8e04a37230a9f78c76c4390b199}

Point uniform inverse scale.

#### point &  [operator/=](#group__point_1gad37f2b9901bf72e2b8fc4d62ba7f99af)(int s) noexcept  {#group__point_1gad37f2b9901bf72e2b8fc4d62ba7f99af}

Point uniform inverse scale.

#### point KLN_VEC_CALL  [operator+](#group__point_1ga7c772c35c230f28573611c707ec46243)(point a,point b) noexcept  {#group__point_1ga7c772c35c230f28573611c707ec46243}

Point addition.

#### point KLN_VEC_CALL  [operator-](#group__point_1ga893da0547e267d631fe79526f1c3d274)(point a,point b) noexcept  {#group__point_1ga893da0547e267d631fe79526f1c3d274}

Point subtraction.

#### point KLN_VEC_CALL  [operator*](#group__point_1gadd07ab21ac8bf227aa0b7b56effda3ed)(point p,float s) noexcept  {#group__point_1gadd07ab21ac8bf227aa0b7b56effda3ed}

Point uniform scale.

#### point KLN_VEC_CALL  [operator*](#group__point_1ga18b3a2d1e891f46f9a59a5b13ab30797)(float s,point p) noexcept  {#group__point_1ga18b3a2d1e891f46f9a59a5b13ab30797}

Point uniform scale.

#### point KLN_VEC_CALL  [operator*](#group__point_1ga1e1b44a57e524d8d6eb2acce6e859f1b)(point p,int s) noexcept  {#group__point_1ga1e1b44a57e524d8d6eb2acce6e859f1b}

Point uniform scale.

#### point KLN_VEC_CALL  [operator*](#group__point_1ga7033b360b0bc9476403ebe099ba86ea3)(int s,point p) noexcept  {#group__point_1ga7033b360b0bc9476403ebe099ba86ea3}

Point uniform scale.

#### point KLN_VEC_CALL  [operator/](#group__point_1ga98d52f70be04ecd1936acb684a7dd3a3)(point p,float s) noexcept  {#group__point_1ga98d52f70be04ecd1936acb684a7dd3a3}

Point uniform inverse scale.

#### point KLN_VEC_CALL  [operator/](#group__point_1ga0ecf62635012f01c124f9294b4dd4a2e)(point p,int s) noexcept  {#group__point_1ga0ecf62635012f01c124f9294b4dd4a2e}

Point uniform inverse scale.

#### point KLN_VEC_CALL  [operator-](#group__point_1ga7b18bf2b94b9e7d2e013eb710dbe11ac)(point p) noexcept  {#group__point_1ga7b18bf2b94b9e7d2e013eb710dbe11ac}

Unary minus (leaves homogeneous coordinate untouched)

#### point KLN_VEC_CALL  [operator~](#group__point_1ga5b6009037927bd8a00156237756f7566)(point p) noexcept  {#group__point_1ga5b6009037927bd8a00156237756f7566}

Reversion operator.

####   [operator point](#group__point_1gac078bf1318b763fe44d89abf77d3b3ef)() const noexcept  {#group__point_1gac078bf1318b763fe44d89abf77d3b3ef}

On its own, the origin occupies no memory, but it can be casted as an entity at any point, at which point it is represented as $\mathbf{e}_{123}$.

