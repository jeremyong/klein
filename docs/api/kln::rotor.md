## struct `kln::rotor` 

```
struct kln::rotor
  : public kln::entity< 0b10 >
```  

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  rotor() = default`  | 
`public  rotor(float ang_rad,float x,float y,float z)`  | 
`public  rotor(` [`entity`](/api/kln::entity#structkln_1_1entity) `< 0b10 > const & other)`  | 
`public void normalize() noexcept`  | 
`public ` [`plane`](/api/kln::plane#structkln_1_1plane) ` KLN_VEC_CALL operator()(` [`plane`](/api/kln::plane#structkln_1_1plane) ` const & p) const noexcept`  | 
`public ` [`point`](/api/kln::point#structkln_1_1point) ` KLN_VEC_CALL operator()(` [`point`](/api/kln::point#structkln_1_1point) ` const & p) const noexcept`  | 
`public ` [`mat4x4`](/api/kln::mat4x4#structkln_1_1mat4x4) ` as_matrix() const noexcept`  | 

### Members

#### `public  rotor() = default`  

#### `public  rotor(float ang_rad,float x,float y,float z)`  

#### `public  rotor(` [`entity`](/api/kln::entity#structkln_1_1entity) `< 0b10 > const & other)`  

#### `public void normalize() noexcept`  

#### `public ` [`plane`](/api/kln::plane#structkln_1_1plane) ` KLN_VEC_CALL operator()(` [`plane`](/api/kln::plane#structkln_1_1plane) ` const & p) const noexcept`  

#### `public ` [`point`](/api/kln::point#structkln_1_1point) ` KLN_VEC_CALL operator()(` [`point`](/api/kln::point#structkln_1_1point) ` const & p) const noexcept`  

#### `public ` [`mat4x4`](/api/kln::mat4x4#structkln_1_1mat4x4) ` as_matrix() const noexcept`  

