## struct `kln::motor` 

```
struct kln::motor
  : public kln::entity< 0b110 >
```  

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  motor() = default`  | 
`public  motor(float a,float b,float c,float d,float e,float f,float g,float h) noexcept`  | 
`public  motor(` [`entity`](/api/kln::entity#structkln_1_1entity) `< 0b110 > const & e) noexcept`  | 
`public void load(float * in) noexcept`  | 
`public void normalize() noexcept`  | 
`public ` [`mat4x4`](/api/kln::mat4x4#structkln_1_1mat4x4) ` as_matrix() const noexcept`  | 
`public ` [`entity`](/api/kln::entity#structkln_1_1entity) `< 0b110 > log() const noexcept`  | 
`public ` [`plane`](/api/kln::plane#structkln_1_1plane) ` KLN_VEC_CALL operator()(` [`plane`](/api/kln::plane#structkln_1_1plane) ` const & p) const noexcept`  | 
`public ` [`point`](/api/kln::point#structkln_1_1point) ` KLN_VEC_CALL operator()(` [`point`](/api/kln::point#structkln_1_1point) ` const & p) const noexcept`  | 
`public ` [`point`](/api/kln::point#structkln_1_1point) ` KLN_VEC_CALL operator()(` [`origin`](/api/kln::origin#structkln_1_1origin) `) const noexcept`  | 

### Members

#### `public  motor() = default`  

#### `public  motor(float a,float b,float c,float d,float e,float f,float g,float h) noexcept`  

#### `public  motor(` [`entity`](/api/kln::entity#structkln_1_1entity) `< 0b110 > const & e) noexcept`  

#### `public void load(float * in) noexcept`  

#### `public void normalize() noexcept`  

#### `public ` [`mat4x4`](/api/kln::mat4x4#structkln_1_1mat4x4) ` as_matrix() const noexcept`  

#### `public ` [`entity`](/api/kln::entity#structkln_1_1entity) `< 0b110 > log() const noexcept`  

#### `public ` [`plane`](/api/kln::plane#structkln_1_1plane) ` KLN_VEC_CALL operator()(` [`plane`](/api/kln::plane#structkln_1_1plane) ` const & p) const noexcept`  

#### `public ` [`point`](/api/kln::point#structkln_1_1point) ` KLN_VEC_CALL operator()(` [`point`](/api/kln::point#structkln_1_1point) ` const & p) const noexcept`  

#### `public ` [`point`](/api/kln::point#structkln_1_1point) ` KLN_VEC_CALL operator()(` [`origin`](/api/kln::origin#structkln_1_1origin) `) const noexcept`  

