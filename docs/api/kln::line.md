## struct `kln::line` {#structkln_1_1line}

```
struct kln::line
  : public kln::entity< 0b110 >
```  

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`line`](#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a)`()`  | 
`public  ` [`line`](#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7)`(float a,float b,float c,float d,float e,float f) noexcept`  | 
`public  ` [`line`](#structkln_1_1line_1af9e56edfe5fe537ef21dd76c1927c5fe)`(` [`entity`](/Klein/api/kln::entity#structkln_1_1entity)`< 0b110 > const & e)`  | 
`public ` [`entity`](/Klein/api/kln::entity#structkln_1_1entity)`< 0b110 > ` [`exp`](#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1)`() const noexcept`  | Line exponentiation

### Members

####   [line](#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a)()  {#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a}

####   [line](#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7)(float a,float b,float c,float d,float e,float f) noexcept  {#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7}

####   [line](#structkln_1_1line_1af9e56edfe5fe537ef21dd76c1927c5fe)( [entity](/Klein/api/kln::entity#structkln_1_1entity)< 0b110 > const & e)  {#structkln_1_1line_1af9e56edfe5fe537ef21dd76c1927c5fe}

####  [entity](/Klein/api/kln::entity#structkln_1_1entity)< 0b110 >  [exp](#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1)() const noexcept  {#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1}

Line exponentiation

The line can be exponentiated to produce a motor that posesses this line as its axis. This routine will be used most often when this line is produced as the logarithm of an existing rotor, then scaled to subdivide or accelerate the motor's action.

