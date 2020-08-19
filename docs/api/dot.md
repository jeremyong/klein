## group `dot` {#group__dot}

The symmetric inner product takes two arguments and contracts the lower graded element to the greater graded element. If lower graded element spans an index that is not contained in the higher graded element, the result is annihilated. Otherwise, the result is the part of the higher graded element "most unlike" the lower graded element. Thus, the symmetric inner product can be thought of as a bidirectional contraction operator.

There is some merit in providing both a left and right contraction operator for explicitness. However, when using Klein, it's generally clear what the interpretation of the symmetric inner product is with respect to the projection on various entities.

!!! example "Angle between planes" 
    ```cpp
        kln::plane a{x1, y1, z1, d1};
        kln::plane b{x2, y2, z2, d2};
    
        // Compute the cos of the angle between two planes
        float cos_ang = a | b;
    ```
    

!!! example "Line to plane through point" 
    ```cpp
        kln::point a{x1, y1, z1};
        kln::plane b{x2, y2, z2, d2};
    
        // The line l contains a and the shortest path from a to plane b.
        line l = a | b;
    ```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float ` [`operator\|`](#group__dot_1gad318da9ce7f0d17c6be4a28606f7055d)`(plane a,plane b) noexcept`             | 
`public plane ` [`operator\|`](#group__dot_1gac5eb4e0be057f05d06fdb47af9c67884)`(plane a,line b) noexcept`             | 
`public plane ` [`operator\|`](#group__dot_1ga6e653adaf2281eb98ea2fb859adebf91)`(line b,plane a) noexcept`             | 
`public plane ` [`operator\|`](#group__dot_1ga95c5016a18aac7ec611fbb69ade553eb)`(plane a,ideal_line b) noexcept`             | 
`public plane ` [`operator\|`](#group__dot_1ga3672748f41be5a0c523e0434bb48da7d)`(ideal_line b,plane a) noexcept`             | 
`public line ` [`operator\|`](#group__dot_1gaf165d820d2709047750f9f9c4e627dc2)`(plane a,point b) noexcept`             | 
`public line ` [`operator\|`](#group__dot_1ga21190874d649c1828316b8133c8c7ec0)`(point a,plane b) noexcept`             | 
`public float ` [`operator\|`](#group__dot_1gab9b2443f7c67a96f08b03ce749565305)`(line a,line b) noexcept`             | 
`public plane ` [`operator\|`](#group__dot_1ga4319b71d30d700e2579c26e181fd16fd)`(point a,line b) noexcept`             | 
`public plane ` [`operator\|`](#group__dot_1ga36111b62f962203bb1a964cd6417b371)`(line b,point a) noexcept`             | 
`public float ` [`operator\|`](#group__dot_1ga4ad7845d5581052aca22d5547ef7d5b1)`(point a,point b) noexcept`             | 

### Members

#### float  [operator|](#group__dot_1gad318da9ce7f0d17c6be4a28606f7055d)(plane a,plane b) noexcept  {#group__dot_1gad318da9ce7f0d17c6be4a28606f7055d}

#### plane  [operator|](#group__dot_1gac5eb4e0be057f05d06fdb47af9c67884)(plane a,line b) noexcept  {#group__dot_1gac5eb4e0be057f05d06fdb47af9c67884}

#### plane  [operator|](#group__dot_1ga6e653adaf2281eb98ea2fb859adebf91)(line b,plane a) noexcept  {#group__dot_1ga6e653adaf2281eb98ea2fb859adebf91}

#### plane  [operator|](#group__dot_1ga95c5016a18aac7ec611fbb69ade553eb)(plane a,ideal_line b) noexcept  {#group__dot_1ga95c5016a18aac7ec611fbb69ade553eb}

#### plane  [operator|](#group__dot_1ga3672748f41be5a0c523e0434bb48da7d)(ideal_line b,plane a) noexcept  {#group__dot_1ga3672748f41be5a0c523e0434bb48da7d}

#### line  [operator|](#group__dot_1gaf165d820d2709047750f9f9c4e627dc2)(plane a,point b) noexcept  {#group__dot_1gaf165d820d2709047750f9f9c4e627dc2}

#### line  [operator|](#group__dot_1ga21190874d649c1828316b8133c8c7ec0)(point a,plane b) noexcept  {#group__dot_1ga21190874d649c1828316b8133c8c7ec0}

#### float  [operator|](#group__dot_1gab9b2443f7c67a96f08b03ce749565305)(line a,line b) noexcept  {#group__dot_1gab9b2443f7c67a96f08b03ce749565305}

#### plane  [operator|](#group__dot_1ga4319b71d30d700e2579c26e181fd16fd)(point a,line b) noexcept  {#group__dot_1ga4319b71d30d700e2579c26e181fd16fd}

#### plane  [operator|](#group__dot_1ga36111b62f962203bb1a964cd6417b371)(line b,point a) noexcept  {#group__dot_1ga36111b62f962203bb1a964cd6417b371}

#### float  [operator|](#group__dot_1ga4ad7845d5581052aca22d5547ef7d5b1)(point a,point b) noexcept  {#group__dot_1ga4ad7845d5581052aca22d5547ef7d5b1}

