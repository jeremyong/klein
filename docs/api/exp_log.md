## group `exp_log` {#group__exp__log}

The group of rotations, translations, and screws (combined rotatation and translation) is *nonlinear*. This means, given say, a rotor $\mathbf{r}$, the rotor $\frac{\mathbf{r}}{2}$ *does not* correspond to half the rotation. Similarly, for a motor $\mathbf{m}$, the motor $n \mathbf{m}$ is not $n$ applications of the motor $\mathbf{m}$. One way we could achieve this is through exponentiation; for example, the motor $\mathbf{m}^3$ will perform the screw action of $\mathbf{m}$ three times. However, repeated multiplication in this fashion lacks both efficiency and numerical stability.

The solution is to take the logarithm of the action which maps the action to a linear space. Using `log(A)`  where `A`  is one of `rotor` , `translator` , or `motor` , we can apply linear scaling to `log(A)` , and then re-exponentiate the result. Using this technique, `exp(n * log(A))`  is equivalent to $\mathbf{A}^n$.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public line KLN_VEC_CALL ` [`log`](#group__exp__log_1ga3c130313451a2328e43f456d85dd4fb6)`(motor m) noexcept`             | Takes the principal branch of the logarithm of the motor, returning a bivector. Exponentiation of that bivector without any changes produces this motor again. Scaling that bivector by $\frac{1}{n}$, re-exponentiating, and taking the result to the $n$th power will also produce this motor again. The logarithm presumes that the motor is normalized.
`public motor KLN_VEC_CALL ` [`exp`](#group__exp__log_1gafd039e0f0dd3daa0bcda9bf813509440)`(line l) noexcept`             | Exponentiate a line to produce a motor that posesses this line as its axis. This routine will be used most often when this line is produced as the logarithm of an existing rotor, then scaled to subdivide or accelerate the motor's action. The line need not be a *simple bivector* for the operation to be well-defined.
`public ideal_line ` [`log`](#group__exp__log_1ga869455da862cba894c72ede161751cf5)`(translator t) noexcept`             | Compute the logarithm of the translator, producing an ideal line axis. In practice, the logarithm of a translator is simply the ideal partition (without the scalar $1$).
`public translator KLN_VEC_CALL ` [`exp`](#group__exp__log_1gad82c9474f26ec967f2d28014f86df6da)`(ideal_line il) noexcept`             | Exponentiate an ideal line to produce a translation.
`public branch ` [`log`](#group__exp__log_1gae6a2c74caa439a32c5f1dd0b44b0d7f3)`(rotor r) noexcept`             | Returns the principal branch of this rotor's logarithm. Invoking `exp`  on the returned `[kln::branch](../../api/undefined#classkln_1_1branch)`  maps back to this rotor.
`public rotor ` [`exp`](#group__exp__log_1ga1aa5a83379532820974c7e86d4bb5a23)`(branch b) noexcept`             | Exponentiate a branch to produce a rotor.
`public rotor ` [`sqrt`](#group__exp__log_1gaaa8057683b4825442c5e23d21cf2e8aa)`(rotor r) noexcept`             | Compute the square root of the provided rotor $r$.
`public rotor ` [`sqrt`](#group__exp__log_1ga3ae618380084d8ef2a58d26fd3672a67)`(branch b) noexcept`             | 
`public translator ` [`sqrt`](#group__exp__log_1ga02407dbecf029cc22be7cd8d1fed5c86)`(translator t) noexcept`             | Compute the square root of the provided translator $t$.
`public motor ` [`sqrt`](#group__exp__log_1ga5b01d5fc4cbc7294069626c9962f8f39)`(motor m) noexcept`             | Compute the square root of the provided motor $m$.

### Members

#### line KLN_VEC_CALL  [log](#group__exp__log_1ga3c130313451a2328e43f456d85dd4fb6)(motor m) noexcept  {#group__exp__log_1ga3c130313451a2328e43f456d85dd4fb6}

Takes the principal branch of the logarithm of the motor, returning a bivector. Exponentiation of that bivector without any changes produces this motor again. Scaling that bivector by $\frac{1}{n}$, re-exponentiating, and taking the result to the $n$th power will also produce this motor again. The logarithm presumes that the motor is normalized.

#### motor KLN_VEC_CALL  [exp](#group__exp__log_1gafd039e0f0dd3daa0bcda9bf813509440)(line l) noexcept  {#group__exp__log_1gafd039e0f0dd3daa0bcda9bf813509440}

Exponentiate a line to produce a motor that posesses this line as its axis. This routine will be used most often when this line is produced as the logarithm of an existing rotor, then scaled to subdivide or accelerate the motor's action. The line need not be a *simple bivector* for the operation to be well-defined.

#### ideal_line  [log](#group__exp__log_1ga869455da862cba894c72ede161751cf5)(translator t) noexcept  {#group__exp__log_1ga869455da862cba894c72ede161751cf5}

Compute the logarithm of the translator, producing an ideal line axis. In practice, the logarithm of a translator is simply the ideal partition (without the scalar $1$).

#### translator KLN_VEC_CALL  [exp](#group__exp__log_1gad82c9474f26ec967f2d28014f86df6da)(ideal_line il) noexcept  {#group__exp__log_1gad82c9474f26ec967f2d28014f86df6da}

Exponentiate an ideal line to produce a translation.

The exponential of an ideal line $a \mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$ is given as:

$$\exp{\left[a\ee_{01} + b\ee_{02} + c\ee_{03}\right]} = 1 +\ a\ee_{01} + b\ee_{02} + c\ee_{03}$$

#### branch  [log](#group__exp__log_1gae6a2c74caa439a32c5f1dd0b44b0d7f3)(rotor r) noexcept  {#group__exp__log_1gae6a2c74caa439a32c5f1dd0b44b0d7f3}

Returns the principal branch of this rotor's logarithm. Invoking `exp`  on the returned `[kln::branch](../../api/undefined#classkln_1_1branch)`  maps back to this rotor.

Given a rotor $\cos\alpha + \sin\alpha\left[a\ee_{23} + b\ee_{31} +\ c\ee_{23}\right]$, the log is computed as simply $\alpha\left[a\ee_{23} + b\ee_{31} + c\ee_{23}\right]$. This map is only well-defined if the rotor is normalized such that $a^2 + b^2 + c^2 = 1$.

#### rotor  [exp](#group__exp__log_1ga1aa5a83379532820974c7e86d4bb5a23)(branch b) noexcept  {#group__exp__log_1ga1aa5a83379532820974c7e86d4bb5a23}

Exponentiate a branch to produce a rotor.

#### rotor  [sqrt](#group__exp__log_1gaaa8057683b4825442c5e23d21cf2e8aa)(rotor r) noexcept  {#group__exp__log_1gaaa8057683b4825442c5e23d21cf2e8aa}

Compute the square root of the provided rotor $r$.

#### rotor  [sqrt](#group__exp__log_1ga3ae618380084d8ef2a58d26fd3672a67)(branch b) noexcept  {#group__exp__log_1ga3ae618380084d8ef2a58d26fd3672a67}

#### translator  [sqrt](#group__exp__log_1ga02407dbecf029cc22be7cd8d1fed5c86)(translator t) noexcept  {#group__exp__log_1ga02407dbecf029cc22be7cd8d1fed5c86}

Compute the square root of the provided translator $t$.

#### motor  [sqrt](#group__exp__log_1ga5b01d5fc4cbc7294069626c9962f8f39)(motor m) noexcept  {#group__exp__log_1ga5b01d5fc4cbc7294069626c9962f8f39}

Compute the square root of the provided motor $m$.

