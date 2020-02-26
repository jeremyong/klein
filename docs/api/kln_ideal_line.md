## struct `kln::ideal_line` {#structkln_1_1ideal__line}

```
struct kln::ideal_line
  : public kln::entity< 0b100 >
```  

An ideal line represents a line at infinity and corresponds to the multivector:

$$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$$

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`ideal_line`](#structkln_1_1ideal__line_1a2f38794571e40000e2a3d68e0863c48f)`() = default`  | 
`public  ` [`ideal_line`](#structkln_1_1ideal__line_1a23cf4cb2763929db4f63dabadc1b9b32)`(float a,float b,float c) noexcept`  | 
`public  ` [`ideal_line`](#structkln_1_1ideal__line_1ac186bdf44379f7eb38c058205ff7fd2c)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)` const & other) noexcept`  | 
`public  ` [`ideal_line`](#structkln_1_1ideal__line_1ad14e9b6cc784c56778784b19f97c195b)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)` && other) noexcept`  | 
`public ` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > ` [`exp`](#structkln_1_1ideal__line_1a5d355ce61318a118b3e92c67656e6b80)`() const noexcept`  | Exponentiate this ideal line to produce a translation. An `entity<0b100>`  is returned instead to avoid a cyclic dependency, but this can be implicitly casted to a `translator` .

### Members

####   [ideal_line](#structkln_1_1ideal__line_1a2f38794571e40000e2a3d68e0863c48f)() = default  {#structkln_1_1ideal__line_1a2f38794571e40000e2a3d68e0863c48f}

####   [ideal_line](#structkln_1_1ideal__line_1a23cf4cb2763929db4f63dabadc1b9b32)(float a,float b,float c) noexcept  {#structkln_1_1ideal__line_1a23cf4cb2763929db4f63dabadc1b9b32}

####   [ideal_line](#structkln_1_1ideal__line_1ac186bdf44379f7eb38c058205ff7fd2c)( [entity](../../api/kln_entity#structkln_1_1entity) const & other) noexcept  {#structkln_1_1ideal__line_1ac186bdf44379f7eb38c058205ff7fd2c}

####   [ideal_line](#structkln_1_1ideal__line_1ad14e9b6cc784c56778784b19f97c195b)( [entity](../../api/kln_entity#structkln_1_1entity) && other) noexcept  {#structkln_1_1ideal__line_1ad14e9b6cc784c56778784b19f97c195b}

####  [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 >  [exp](#structkln_1_1ideal__line_1a5d355ce61318a118b3e92c67656e6b80)() const noexcept  {#structkln_1_1ideal__line_1a5d355ce61318a118b3e92c67656e6b80}

Exponentiate this ideal line to produce a translation. An `entity<0b100>`  is returned instead to avoid a cyclic dependency, but this can be implicitly casted to a `translator` .

The exponential of an ideal line $a \mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$ is given as:

$$\exp{\left[a\ee_{01} + b\ee_{02} + c\ee_{03}\right]} = 1 +\ a\ee_{01} + b\ee_{02} + c\ee_{03}$$

If this line is aliasing a portion of an existing translator, the original translator can be used directly.

