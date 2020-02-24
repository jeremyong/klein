## struct `kln::line` {#structkln_1_1line}

```
struct kln::line
  : public kln::entity< 0b110 >
```  

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`line`](#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a)`()`  | 
`public  ` [`line`](#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7)`(float a,float b,float c,float d,float e,float f) noexcept`  | A line is specifed by 6 coordinates which correspond to the line's [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates). The coordinates specified in this way correspond to the following multivector:
`public  ` [`line`](#structkln_1_1line_1af9e56edfe5fe537ef21dd76c1927c5fe)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > const & e)`  | 
`public  ` [`line`](#structkln_1_1line_1a020bc12c8cf7e73c7f440a3ce4c7edb0)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b100 > const & e)`  | 
`public  ` [`line`](#structkln_1_1line_1a36115e3464ff63cb869dfc09d876d1be)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b10 > const & e)`  | 
`public float ` [`squared_norm`](#structkln_1_1line_1af9fdfa8ac229420aa1649100ee573bf8)`()`  | If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
`public float ` [`norm`](#structkln_1_1line_1acbce68119eab96bcc0ec3918dfa4691c)`()`  | Returns the square root of the quantity produced by `squared_norm` .
`public ` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > ` [`exp`](#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1)`() const noexcept`  | Line exponentiation

### Members

####   [line](#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a)()  {#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a}

####   [line](#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7)(float a,float b,float c,float d,float e,float f) noexcept  {#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7}

A line is specifed by 6 coordinates which correspond to the line's [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates). The coordinates specified in this way correspond to the following multivector:

$$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03} +\ d\mathbf{e}_{23} + e\mathbf{e}_{31} + f\mathbf{e}_{12}$$

####   [line](#structkln_1_1line_1af9e56edfe5fe537ef21dd76c1927c5fe)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 > const & e)  {#structkln_1_1line_1af9e56edfe5fe537ef21dd76c1927c5fe}

####   [line](#structkln_1_1line_1a020bc12c8cf7e73c7f440a3ce4c7edb0)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b100 > const & e)  {#structkln_1_1line_1a020bc12c8cf7e73c7f440a3ce4c7edb0}

####   [line](#structkln_1_1line_1a36115e3464ff63cb869dfc09d876d1be)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b10 > const & e)  {#structkln_1_1line_1a36115e3464ff63cb869dfc09d876d1be}

#### float  [squared_norm](#structkln_1_1line_1af9fdfa8ac229420aa1649100ee573bf8)()  {#structkln_1_1line_1af9fdfa8ac229420aa1649100ee573bf8}

If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.

#### float  [norm](#structkln_1_1line_1acbce68119eab96bcc0ec3918dfa4691c)()  {#structkln_1_1line_1acbce68119eab96bcc0ec3918dfa4691c}

Returns the square root of the quantity produced by `squared_norm` .

####  [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 >  [exp](#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1)() const noexcept  {#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1}

Line exponentiation

The line can be exponentiated to produce a motor that posesses this line as its axis. This routine will be used most often when this line is produced as the logarithm of an existing rotor, then scaled to subdivide or accelerate the motor's action.

