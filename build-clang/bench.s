	.text
	.intel_syntax noprefix
	.file	"bench.cpp"
	.section	.text._ZNSt13random_deviceD2Ev,"axG",@progbits,_ZNSt13random_deviceD2Ev,comdat
	.weak	_ZNSt13random_deviceD2Ev # -- Begin function _ZNSt13random_deviceD2Ev
	.p2align	4, 0x90
	.type	_ZNSt13random_deviceD2Ev,@function
_ZNSt13random_deviceD2Ev:               # @_ZNSt13random_deviceD2Ev
	.cfi_startproc
# %bb.0:
	jmp	_ZNSt13random_device7_M_finiEv@PLT # TAILCALL
.Lfunc_end0:
	.size	_ZNSt13random_deviceD2Ev, .Lfunc_end0-_ZNSt13random_deviceD2Ev
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3               # -- Begin function _Z12random_rotorv
.LCPI1_0:
	.quad	4746794007240114176     # double 2147483646
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI1_1:
	.long	1073741824              # float 2
.LCPI1_2:
	.long	1593835520              # float 9.22337203E+18
.LCPI1_3:
	.long	1065353216              # float 1
.LCPI1_4:
	.long	1325400064              # float 2.14748365E+9
.LCPI1_5:
	.long	3212836864              # float -1
.LCPI1_6:
	.long	1056964608              # float 0.5
	.text
	.globl	_Z12random_rotorv
	.p2align	4, 0x90
	.type	_Z12random_rotorv,@function
_Z12random_rotorv:                      # @_Z12random_rotorv
	.cfi_startproc
# %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	sub	rsp, 264
	.cfi_def_cfa_offset 288
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	mov	r14, rdi
	fld	qword ptr [rip + .LCPI1_0]
	fld	st(0)
	fstp	tbyte ptr [rsp + 32]    # 10-byte Folded Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 64]    # 10-byte Folded Spill
	fld	dword ptr [rip + .LCPI1_1]
	fld	st(0)
	fstp	tbyte ptr [rsp + 96]    # 10-byte Folded Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 64]    # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	dword ptr [rip + .LCPI1_2]
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fld	st(1)
	fstp	tbyte ptr [rsp + 192]   # 10-byte Folded Spill
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 240]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 240]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	movabs	rbx, 8589934597
	test	dil, 1
	jne	.LBB1_2
# %bb.1:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI1_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB1_12
	jmp	.LBB1_7
.LBB1_2:                                # %select.unfold.i.i.i.i.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB1_3
# %bb.4:                                # %select.unfold.i.i.i.i.prol
	cvtsi2ss	xmm0, rdx
	jmp	.LBB1_5
.LBB1_3:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB1_5:                                # %select.unfold.i.i.i.i.prol
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI1_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB1_12
.LBB1_7:
	movss	xmm2, dword ptr [rip + .LCPI1_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB1_8
	.p2align	4, 0x90
.LBB1_17:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB1_12 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB1_18:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB1_12 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 164], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 164]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 160]
	movss	xmm2, dword ptr [rsp + 160] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB1_8
.LBB1_12:                               # %select.unfold.i.i.i.i
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB1_13
# %bb.14:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB1_12 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB1_15
	.p2align	4, 0x90
.LBB1_13:                               #   in Loop: Header=BB1_12 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB1_15:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB1_12 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 172], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 172]
	fstp	dword ptr [rsp + 168]
	movss	xmm2, dword ptr [rsp + 168] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB1_17
# %bb.16:                               #   in Loop: Header=BB1_12 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB1_18
.LBB1_8:                                # %.unr-lcssa91
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI1_3]
	jae	.LBB1_9
.LBB1_10:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit
	movss	dword ptr [rsp + 56], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 92], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 28], xmm0 # 4-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 64]    # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 96]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 64]    # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 192]   # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 232]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 232]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB1_19
# %bb.11:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI1_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB1_29
	jmp	.LBB1_24
.LBB1_19:                               # %select.unfold.i.i.i.i6.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB1_20
# %bb.21:                               # %select.unfold.i.i.i.i6.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB1_22
.LBB1_20:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB1_22:                               # %select.unfold.i.i.i.i6.prol
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI1_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB1_29
.LBB1_24:
	movss	xmm2, dword ptr [rip + .LCPI1_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB1_25
	.p2align	4, 0x90
.LBB1_34:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB1_29 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB1_35:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB1_29 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 148], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 148]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 144]
	movss	xmm2, dword ptr [rsp + 144] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB1_25
.LBB1_29:                               # %select.unfold.i.i.i.i6
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB1_30
# %bb.31:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB1_29 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB1_32
	.p2align	4, 0x90
.LBB1_30:                               #   in Loop: Header=BB1_29 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB1_32:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB1_29 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 156], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 156]
	fstp	dword ptr [rsp + 152]
	movss	xmm2, dword ptr [rsp + 152] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB1_34
# %bb.33:                               #   in Loop: Header=BB1_29 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB1_35
.LBB1_25:                               # %.unr-lcssa87
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI1_3]
	jae	.LBB1_26
.LBB1_27:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit8
	movss	dword ptr [rsp + 88], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 60], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 64], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 176]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 96]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 176]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 192]   # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 224]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 224]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB1_36
# %bb.28:
	xorps	xmm0, xmm0
	movss	xmm3, dword ptr [rip + .LCPI1_3] # xmm3 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	movaps	xmm2, xmmword ptr [rsp + 64] # 16-byte Reload
	cmp	rsi, 2
	jae	.LBB1_46
	jmp	.LBB1_41
.LBB1_36:                               # %select.unfold.i.i.i.i14.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB1_37
# %bb.38:                               # %select.unfold.i.i.i.i14.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB1_39
.LBB1_37:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB1_39:                               # %select.unfold.i.i.i.i14.prol
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	movaps	xmm2, xmmword ptr [rsp + 64] # 16-byte Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm3, dword ptr [rip + .LCPI1_4] # xmm3 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB1_46
.LBB1_41:
	movss	xmm3, dword ptr [rip + .LCPI1_4] # xmm3 = mem[0],zero,zero,zero
	jmp	.LBB1_42
	.p2align	4, 0x90
.LBB1_51:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB1_46 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB1_52:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB1_46 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm3
	movss	dword ptr [rsp + 132], xmm3
	fld	st(0)
	fmul	dword ptr [rsp + 132]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 128]
	movss	xmm3, dword ptr [rsp + 128] # xmm3 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB1_42
.LBB1_46:                               # %select.unfold.i.i.i.i14
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB1_47
# %bb.48:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB1_46 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB1_49
	.p2align	4, 0x90
.LBB1_47:                               #   in Loop: Header=BB1_46 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB1_49:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB1_46 Depth=1
	mulss	xmm1, xmm3
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 140], xmm3
	fld	st(0)
	fmul	dword ptr [rsp + 140]
	fstp	dword ptr [rsp + 136]
	movss	xmm3, dword ptr [rsp + 136] # xmm3 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB1_51
# %bb.50:                               #   in Loop: Header=BB1_46 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB1_52
.LBB1_42:                               # %.unr-lcssa83
	divss	xmm0, xmm3
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI1_3]
	jae	.LBB1_43
.LBB1_44:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit16
	movss	dword ptr [rsp + 52], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 60] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm2
	movss	dword ptr [rsp + 60], xmm0 # 4-byte Spill
	movss	xmm1, dword ptr [rip + _ZL4dist.0.1] # xmm1 = mem[0],zero,zero,zero
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 176], xmm0 # 16-byte Spill
	subss	xmm1, xmm0
	movss	dword ptr [rsp + 108], xmm1 # 4-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 252]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 96]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 252]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 192]   # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 216]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 216]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB1_53
# %bb.45:
	xorps	xmm0, xmm0
	movss	xmm1, dword ptr [rip + .LCPI1_3] # xmm1 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	movss	xmm3, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	movss	xmm4, dword ptr [rsp + 92] # 4-byte Reload
                                        # xmm4 = mem[0],zero,zero,zero
	movss	xmm5, dword ptr [rsp + 88] # 4-byte Reload
                                        # xmm5 = mem[0],zero,zero,zero
	movss	xmm6, dword ptr [rsp + 52] # 4-byte Reload
                                        # xmm6 = mem[0],zero,zero,zero
	jmp	.LBB1_57
.LBB1_53:                               # %select.unfold.i.i.i.i22.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	movss	xmm3, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	movss	xmm4, dword ptr [rsp + 92] # 4-byte Reload
                                        # xmm4 = mem[0],zero,zero,zero
	movss	xmm5, dword ptr [rsp + 88] # 4-byte Reload
                                        # xmm5 = mem[0],zero,zero,zero
	js	.LBB1_54
# %bb.55:                               # %select.unfold.i.i.i.i22.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB1_56
.LBB1_54:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB1_56:                               # %select.unfold.i.i.i.i22.prol
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	movss	xmm6, dword ptr [rsp + 52] # 4-byte Reload
                                        # xmm6 = mem[0],zero,zero,zero
	add	rcx, rax
	add	rdi, -1
	movss	xmm1, dword ptr [rip + .LCPI1_4] # xmm1 = mem[0],zero,zero,zero
.LBB1_57:                               # %select.unfold.i.i.i.i22.prol.loopexit
	subss	xmm4, xmm3
	mulss	xmm5, dword ptr [rsp + 60] # 4-byte Folded Reload
	mulss	xmm6, dword ptr [rsp + 108] # 4-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB1_63
# %bb.58:
	fstp	st(0)
	movss	xmm1, dword ptr [rip + .LCPI1_4] # xmm1 = mem[0],zero,zero,zero
	fldz
	jmp	.LBB1_59
	.p2align	4, 0x90
.LBB1_68:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB1_63 Depth=1
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rdx
.LBB1_69:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB1_63 Depth=1
	add	rcx, rax
	mulss	xmm2, xmm1
	movss	dword ptr [rsp + 116], xmm1
	fld	st(0)
	fmul	dword ptr [rsp + 116]
	addss	xmm0, xmm2
	fstp	dword ptr [rsp + 112]
	movss	xmm1, dword ptr [rsp + 112] # xmm1 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB1_59
.LBB1_63:                               # %select.unfold.i.i.i.i22
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB1_64
# %bb.65:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB1_63 Depth=1
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rcx
	jmp	.LBB1_66
	.p2align	4, 0x90
.LBB1_64:                               #   in Loop: Header=BB1_63 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rcx
	addss	xmm2, xmm2
.LBB1_66:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB1_63 Depth=1
	mulss	xmm2, xmm1
	addss	xmm0, xmm2
	movss	dword ptr [rsp + 124], xmm1
	fld	st(0)
	fmul	dword ptr [rsp + 124]
	fstp	dword ptr [rsp + 120]
	movss	xmm1, dword ptr [rsp + 120] # xmm1 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB1_68
# %bb.67:                               #   in Loop: Header=BB1_63 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rdx
	addss	xmm2, xmm2
	jmp	.LBB1_69
.LBB1_59:                               # %.unr-lcssa
	fstp	st(0)
	divss	xmm0, xmm1
	movss	xmm2, dword ptr [rsp + 56] # 4-byte Reload
                                        # xmm2 = mem[0],zero,zero,zero
	mulss	xmm2, xmm4
	movaps	xmm4, xmmword ptr [rsp + 64] # 16-byte Reload
	addss	xmm4, xmm5
	movaps	xmm5, xmmword ptr [rsp + 176] # 16-byte Reload
	addss	xmm5, xmm6
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI1_3]
	movaps	xmmword ptr [rsp + 64], xmm4 # 16-byte Spill
	movaps	xmmword ptr [rsp + 176], xmm5 # 16-byte Spill
	jae	.LBB1_60
.LBB1_61:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit24
	addss	xmm3, xmm2
	movss	xmm2, dword ptr [rip + _ZL4dist.0.1] # xmm2 = mem[0],zero,zero,zero
	movss	xmm1, dword ptr [rip + _ZL4dist.0.0] # xmm1 = mem[0],zero,zero,zero
	subss	xmm2, xmm1
	mulss	xmm2, xmm0
	addss	xmm2, xmm1
	movaps	xmm0, xmm4
	mulss	xmm0, xmm4
	movaps	xmm1, xmm5
	mulss	xmm1, xmm5
	addss	xmm1, xmm0
	movaps	xmmword ptr [rsp + 32], xmm2 # 16-byte Spill
	movaps	xmm0, xmm2
	mulss	xmm0, xmm2
	addss	xmm0, xmm1
	xorps	xmm1, xmm1
	ucomiss	xmm0, xmm1
	jb	.LBB1_70
# %bb.62:
	sqrtss	xmm0, xmm0
	jmp	.LBB1_71
.LBB1_70:                               # %call.sqrt
	movss	dword ptr [rsp + 28], xmm3 # 4-byte Spill
	call	sqrtf@PLT
	movss	xmm3, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
.LBB1_71:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit24.split
	movss	xmm1, dword ptr [rip + .LCPI1_5] # xmm1 = mem[0],zero,zero,zero
	divss	xmm1, xmm0
	movss	dword ptr [rsp + 96], xmm1 # 4-byte Spill
	mulss	xmm3, dword ptr [rip + .LCPI1_6]
	movss	dword ptr [rsp + 28], xmm3 # 4-byte Spill
	movaps	xmm0, xmm3
	call	cosf@PLT
	movaps	xmmword ptr [rsp + 192], xmm0 # 16-byte Spill
	movss	xmm0, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	call	sinf@PLT
	mulss	xmm0, dword ptr [rsp + 96] # 4-byte Folded Reload
	movaps	xmm3, xmmword ptr [rsp + 32] # 16-byte Reload
	mulss	xmm3, xmm0
	movaps	xmm2, xmmword ptr [rsp + 176] # 16-byte Reload
	mulss	xmm2, xmm0
	movaps	xmm1, xmmword ptr [rsp + 64] # 16-byte Reload
	mulss	xmm1, xmm0
	movaps	xmm0, xmmword ptr [rsp + 192] # 16-byte Reload
	insertps	xmm0, xmm3, 16  # xmm0 = xmm0[0],xmm3[0],xmm0[2,3]
	insertps	xmm0, xmm2, 32  # xmm0 = xmm0[0,1],xmm2[0],xmm0[3]
	insertps	xmm0, xmm1, 48  # xmm0 = xmm0[0,1,2],xmm1[0]
	movaps	xmmword ptr [r14], xmm0
	mov	rax, r14
	add	rsp, 264
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.LBB1_9:
	.cfi_def_cfa_offset 288
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI1_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	jmp	.LBB1_10
.LBB1_26:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI1_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	jmp	.LBB1_27
.LBB1_43:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI1_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	movaps	xmm2, xmmword ptr [rsp + 64] # 16-byte Reload
	fld	tbyte ptr [rsp + 32]    # 10-byte Folded Reload
	jmp	.LBB1_44
.LBB1_60:
	movss	xmm0, dword ptr [rip + .LCPI1_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	movss	dword ptr [rsp + 56], xmm2 # 4-byte Spill
	call	nextafterf@PLT
	movaps	xmm5, xmmword ptr [rsp + 176] # 16-byte Reload
	movaps	xmm4, xmmword ptr [rsp + 64] # 16-byte Reload
	movss	xmm3, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	movss	xmm2, dword ptr [rsp + 56] # 4-byte Reload
                                        # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB1_61
.Lfunc_end1:
	.size	_Z12random_rotorv, .Lfunc_end1-_Z12random_rotorv
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3               # -- Begin function _Z12random_motorv
.LCPI2_0:
	.quad	4746794007240114176     # double 2147483646
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI2_1:
	.long	1073741824              # float 2
.LCPI2_2:
	.long	1593835520              # float 9.22337203E+18
.LCPI2_3:
	.long	1065353216              # float 1
.LCPI2_4:
	.long	1325400064              # float 2.14748365E+9
	.text
	.globl	_Z12random_motorv
	.p2align	4, 0x90
	.type	_Z12random_motorv,@function
_Z12random_motorv:                      # @_Z12random_motorv
	.cfi_startproc
# %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	sub	rsp, 488
	.cfi_def_cfa_offset 512
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	mov	r14, rdi
	fld	qword ptr [rip + .LCPI2_0]
	fld	st(0)
	fstp	tbyte ptr [rsp + 16]    # 10-byte Folded Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 36]    # 10-byte Folded Spill
	fld	dword ptr [rip + .LCPI2_1]
	fld	st(0)
	fstp	tbyte ptr [rsp + 48]    # 10-byte Folded Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	dword ptr [rip + .LCPI2_2]
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fld	st(1)
	fstp	tbyte ptr [rsp + 36]    # 10-byte Folded Spill
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 464]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 464]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	movabs	rbx, 8589934597
	test	dil, 1
	jne	.LBB2_2
# %bb.1:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI2_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_12
	jmp	.LBB2_7
.LBB2_2:                                # %select.unfold.i.i.i.i.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB2_3
# %bb.4:                                # %select.unfold.i.i.i.i.prol
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_5
.LBB2_3:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_5:                                # %select.unfold.i.i.i.i.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_12
.LBB2_7:
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB2_8
	.p2align	4, 0x90
.LBB2_17:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB2_12 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_18:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB2_12 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 292], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 292]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 288]
	movss	xmm2, dword ptr [rsp + 288] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_8
.LBB2_12:                               # %select.unfold.i.i.i.i
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_13
# %bb.14:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB2_12 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_15
	.p2align	4, 0x90
.LBB2_13:                               #   in Loop: Header=BB2_12 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_15:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB2_12 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 300], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 300]
	fstp	dword ptr [rsp + 296]
	movss	xmm2, dword ptr [rsp + 296] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_17
# %bb.16:                               #   in Loop: Header=BB2_12 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_18
.LBB2_8:                                # %.unr-lcssa199
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_9
.LBB2_10:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit
	movss	dword ptr [rsp + 80], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 32], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 368], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 132]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 132]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 456]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 456]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_19
# %bb.11:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI2_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_29
	jmp	.LBB2_24
.LBB2_19:                               # %select.unfold.i.i.i.i6.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB2_20
# %bb.21:                               # %select.unfold.i.i.i.i6.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_22
.LBB2_20:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_22:                               # %select.unfold.i.i.i.i6.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_29
.LBB2_24:
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB2_25
	.p2align	4, 0x90
.LBB2_34:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB2_29 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_35:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB2_29 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 276], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 276]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 272]
	movss	xmm2, dword ptr [rsp + 272] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_25
.LBB2_29:                               # %select.unfold.i.i.i.i6
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_30
# %bb.31:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB2_29 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_32
	.p2align	4, 0x90
.LBB2_30:                               #   in Loop: Header=BB2_29 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_32:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB2_29 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 284], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 284]
	fstp	dword ptr [rsp + 280]
	movss	xmm2, dword ptr [rsp + 280] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_34
# %bb.33:                               #   in Loop: Header=BB2_29 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_35
.LBB2_25:                               # %.unr-lcssa195
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_26
.LBB2_27:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit8
	movss	dword ptr [rsp + 76], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 132], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 352], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 120]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 120]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 448]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 448]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_36
# %bb.28:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI2_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_46
	jmp	.LBB2_41
.LBB2_36:                               # %select.unfold.i.i.i.i14.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB2_37
# %bb.38:                               # %select.unfold.i.i.i.i14.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_39
.LBB2_37:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_39:                               # %select.unfold.i.i.i.i14.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_46
.LBB2_41:
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB2_42
	.p2align	4, 0x90
.LBB2_51:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB2_46 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_52:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB2_46 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 260], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 260]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 256]
	movss	xmm2, dword ptr [rsp + 256] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_42
.LBB2_46:                               # %select.unfold.i.i.i.i14
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_47
# %bb.48:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB2_46 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_49
	.p2align	4, 0x90
.LBB2_47:                               #   in Loop: Header=BB2_46 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_49:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB2_46 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 268], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 268]
	fstp	dword ptr [rsp + 264]
	movss	xmm2, dword ptr [rsp + 264] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_51
# %bb.50:                               #   in Loop: Header=BB2_46 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_52
.LBB2_42:                               # %.unr-lcssa191
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_43
.LBB2_44:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit16
	movss	dword ptr [rsp + 72], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 120], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 336], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 108]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 108]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 440]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 440]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_53
# %bb.45:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI2_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_63
	jmp	.LBB2_58
.LBB2_53:                               # %select.unfold.i.i.i.i22.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB2_54
# %bb.55:                               # %select.unfold.i.i.i.i22.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_56
.LBB2_54:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_56:                               # %select.unfold.i.i.i.i22.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_63
.LBB2_58:
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB2_59
	.p2align	4, 0x90
.LBB2_68:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB2_63 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_69:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB2_63 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 244], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 244]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 240]
	movss	xmm2, dword ptr [rsp + 240] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_59
.LBB2_63:                               # %select.unfold.i.i.i.i22
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_64
# %bb.65:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB2_63 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_66
	.p2align	4, 0x90
.LBB2_64:                               #   in Loop: Header=BB2_63 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_66:                               # %select.unfold.i.i.i.i22
                                        #   in Loop: Header=BB2_63 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 252], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 252]
	fstp	dword ptr [rsp + 248]
	movss	xmm2, dword ptr [rsp + 248] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_68
# %bb.67:                               #   in Loop: Header=BB2_63 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_69
.LBB2_59:                               # %.unr-lcssa187
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_60
.LBB2_61:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit24
	movss	dword ptr [rsp + 68], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 108], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 320], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 96]    # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 96]    # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 432]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 432]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_70
# %bb.62:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI2_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_80
	jmp	.LBB2_75
.LBB2_70:                               # %select.unfold.i.i.i.i30.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB2_71
# %bb.72:                               # %select.unfold.i.i.i.i30.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_73
.LBB2_71:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_73:                               # %select.unfold.i.i.i.i30.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_80
.LBB2_75:
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB2_76
	.p2align	4, 0x90
.LBB2_85:                               # %select.unfold.i.i.i.i30
                                        #   in Loop: Header=BB2_80 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_86:                               # %select.unfold.i.i.i.i30
                                        #   in Loop: Header=BB2_80 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 228], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 228]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 224]
	movss	xmm2, dword ptr [rsp + 224] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_76
.LBB2_80:                               # %select.unfold.i.i.i.i30
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_81
# %bb.82:                               # %select.unfold.i.i.i.i30
                                        #   in Loop: Header=BB2_80 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_83
	.p2align	4, 0x90
.LBB2_81:                               #   in Loop: Header=BB2_80 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_83:                               # %select.unfold.i.i.i.i30
                                        #   in Loop: Header=BB2_80 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 236], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 236]
	fstp	dword ptr [rsp + 232]
	movss	xmm2, dword ptr [rsp + 232] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_85
# %bb.84:                               #   in Loop: Header=BB2_80 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_86
.LBB2_76:                               # %.unr-lcssa183
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_77
.LBB2_78:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit32
	movss	dword ptr [rsp + 64], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 96], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 304], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 84]    # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 84]    # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 424]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 424]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_87
# %bb.79:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI2_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_97
	jmp	.LBB2_92
.LBB2_87:                               # %select.unfold.i.i.i.i38.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB2_88
# %bb.89:                               # %select.unfold.i.i.i.i38.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_90
.LBB2_88:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_90:                               # %select.unfold.i.i.i.i38.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_97
.LBB2_92:
	movss	xmm2, dword ptr [rip + .LCPI2_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB2_93
	.p2align	4, 0x90
.LBB2_102:                              # %select.unfold.i.i.i.i38
                                        #   in Loop: Header=BB2_97 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_103:                              # %select.unfold.i.i.i.i38
                                        #   in Loop: Header=BB2_97 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 212], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 212]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 208]
	movss	xmm2, dword ptr [rsp + 208] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_93
.LBB2_97:                               # %select.unfold.i.i.i.i38
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_98
# %bb.99:                               # %select.unfold.i.i.i.i38
                                        #   in Loop: Header=BB2_97 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_100
	.p2align	4, 0x90
.LBB2_98:                               #   in Loop: Header=BB2_97 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_100:                              # %select.unfold.i.i.i.i38
                                        #   in Loop: Header=BB2_97 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 220], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 220]
	fstp	dword ptr [rsp + 216]
	movss	xmm2, dword ptr [rsp + 216] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_102
# %bb.101:                              #   in Loop: Header=BB2_97 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_103
.LBB2_93:                               # %.unr-lcssa179
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_94
.LBB2_95:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit40
	movss	dword ptr [rsp + 60], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 84], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 144], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 384]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 384]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 416]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 416]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_104
# %bb.96:
	xorps	xmm0, xmm0
	movss	xmm6, dword ptr [rip + .LCPI2_3] # xmm6 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movaps	xmm2, xmmword ptr [rsp + 368] # 16-byte Reload
	movaps	xmm3, xmmword ptr [rsp + 352] # 16-byte Reload
	movaps	xmm4, xmmword ptr [rsp + 336] # 16-byte Reload
	movaps	xmm5, xmmword ptr [rsp + 320] # 16-byte Reload
	movaps	xmm8, xmmword ptr [rsp + 304] # 16-byte Reload
	movaps	xmm7, xmmword ptr [rsp + 144] # 16-byte Reload
	cmp	rsi, 2
	jae	.LBB2_114
	jmp	.LBB2_109
.LBB2_104:                              # %select.unfold.i.i.i.i46.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	movaps	xmm2, xmmword ptr [rsp + 368] # 16-byte Reload
	movaps	xmm3, xmmword ptr [rsp + 352] # 16-byte Reload
	movaps	xmm4, xmmword ptr [rsp + 336] # 16-byte Reload
	movaps	xmm5, xmmword ptr [rsp + 320] # 16-byte Reload
	movaps	xmm8, xmmword ptr [rsp + 304] # 16-byte Reload
	js	.LBB2_105
# %bb.106:                              # %select.unfold.i.i.i.i46.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_107
.LBB2_105:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_107:                              # %select.unfold.i.i.i.i46.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movaps	xmm7, xmmword ptr [rsp + 144] # 16-byte Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm6, dword ptr [rip + .LCPI2_4] # xmm6 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB2_114
.LBB2_109:
	movss	xmm6, dword ptr [rip + .LCPI2_4] # xmm6 = mem[0],zero,zero,zero
	jmp	.LBB2_110
	.p2align	4, 0x90
.LBB2_119:                              # %select.unfold.i.i.i.i46
                                        #   in Loop: Header=BB2_114 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB2_120:                              # %select.unfold.i.i.i.i46
                                        #   in Loop: Header=BB2_114 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm6
	movss	dword ptr [rsp + 196], xmm6
	fld	st(0)
	fmul	dword ptr [rsp + 196]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 192]
	movss	xmm6, dword ptr [rsp + 192] # xmm6 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_110
.LBB2_114:                              # %select.unfold.i.i.i.i46
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_115
# %bb.116:                              # %select.unfold.i.i.i.i46
                                        #   in Loop: Header=BB2_114 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB2_117
	.p2align	4, 0x90
.LBB2_115:                              #   in Loop: Header=BB2_114 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB2_117:                              # %select.unfold.i.i.i.i46
                                        #   in Loop: Header=BB2_114 Depth=1
	mulss	xmm1, xmm6
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 204], xmm6
	fld	st(0)
	fmul	dword ptr [rsp + 204]
	fstp	dword ptr [rsp + 200]
	movss	xmm6, dword ptr [rsp + 200] # xmm6 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_119
# %bb.118:                              #   in Loop: Header=BB2_114 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB2_120
.LBB2_110:                              # %.unr-lcssa175
	divss	xmm0, xmm6
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_111
.LBB2_112:                              # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit48
	movss	dword ptr [rsp + 28], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 32] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm2
	movss	dword ptr [rsp + 32], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 132] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm3
	movss	dword ptr [rsp + 132], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 120] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm4
	movss	dword ptr [rsp + 120], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 108] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm5
	movss	dword ptr [rsp + 108], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 96] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm8
	movss	dword ptr [rsp + 96], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 84] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm7
	movss	dword ptr [rsp + 84], xmm0 # 4-byte Spill
	movss	xmm1, dword ptr [rip + _ZL4dist.0.1] # xmm1 = mem[0],zero,zero,zero
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 384], xmm0 # 16-byte Spill
	subss	xmm1, xmm0
	movss	dword ptr [rsp + 172], xmm1 # 4-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 476]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 48]    # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 476]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 408]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 408]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB2_121
# %bb.113:
	xorps	xmm0, xmm0
	movss	xmm1, dword ptr [rip + .LCPI2_3] # xmm1 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movss	xmm3, dword ptr [rsp + 80] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	movss	xmm4, dword ptr [rsp + 76] # 4-byte Reload
                                        # xmm4 = mem[0],zero,zero,zero
	movss	xmm5, dword ptr [rsp + 72] # 4-byte Reload
                                        # xmm5 = mem[0],zero,zero,zero
	movss	xmm6, dword ptr [rsp + 68] # 4-byte Reload
                                        # xmm6 = mem[0],zero,zero,zero
	movss	xmm7, dword ptr [rsp + 64] # 4-byte Reload
                                        # xmm7 = mem[0],zero,zero,zero
	movss	xmm8, dword ptr [rsp + 60] # 4-byte Reload
                                        # xmm8 = mem[0],zero,zero,zero
	movss	xmm10, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm10 = mem[0],zero,zero,zero
	jmp	.LBB2_125
.LBB2_121:                              # %select.unfold.i.i.i.i54.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	movss	xmm3, dword ptr [rsp + 80] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	movss	xmm4, dword ptr [rsp + 76] # 4-byte Reload
                                        # xmm4 = mem[0],zero,zero,zero
	movss	xmm5, dword ptr [rsp + 72] # 4-byte Reload
                                        # xmm5 = mem[0],zero,zero,zero
	movss	xmm6, dword ptr [rsp + 68] # 4-byte Reload
                                        # xmm6 = mem[0],zero,zero,zero
	movss	xmm7, dword ptr [rsp + 64] # 4-byte Reload
                                        # xmm7 = mem[0],zero,zero,zero
	movss	xmm8, dword ptr [rsp + 60] # 4-byte Reload
                                        # xmm8 = mem[0],zero,zero,zero
	js	.LBB2_122
# %bb.123:                              # %select.unfold.i.i.i.i54.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB2_124
.LBB2_122:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB2_124:                              # %select.unfold.i.i.i.i54.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movss	xmm10, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm10 = mem[0],zero,zero,zero
	add	rcx, rax
	add	rdi, -1
	movss	xmm1, dword ptr [rip + .LCPI2_4] # xmm1 = mem[0],zero,zero,zero
.LBB2_125:                              # %select.unfold.i.i.i.i54.prol.loopexit
	mulss	xmm3, dword ptr [rsp + 32] # 4-byte Folded Reload
	mulss	xmm4, dword ptr [rsp + 132] # 4-byte Folded Reload
	mulss	xmm5, dword ptr [rsp + 120] # 4-byte Folded Reload
	mulss	xmm6, dword ptr [rsp + 108] # 4-byte Folded Reload
	mulss	xmm7, dword ptr [rsp + 96] # 4-byte Folded Reload
	mulss	xmm8, dword ptr [rsp + 84] # 4-byte Folded Reload
	mulss	xmm10, dword ptr [rsp + 172] # 4-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB2_130
# %bb.126:
	fstp	st(0)
	movss	xmm1, dword ptr [rip + .LCPI2_4] # xmm1 = mem[0],zero,zero,zero
	fldz
	jmp	.LBB2_127
	.p2align	4, 0x90
.LBB2_135:                              # %select.unfold.i.i.i.i54
                                        #   in Loop: Header=BB2_130 Depth=1
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rdx
.LBB2_136:                              # %select.unfold.i.i.i.i54
                                        #   in Loop: Header=BB2_130 Depth=1
	add	rcx, rax
	mulss	xmm2, xmm1
	movss	dword ptr [rsp + 180], xmm1
	fld	st(0)
	fmul	dword ptr [rsp + 180]
	addss	xmm0, xmm2
	fstp	dword ptr [rsp + 176]
	movss	xmm1, dword ptr [rsp + 176] # xmm1 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB2_127
.LBB2_130:                              # %select.unfold.i.i.i.i54
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB2_131
# %bb.132:                              # %select.unfold.i.i.i.i54
                                        #   in Loop: Header=BB2_130 Depth=1
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rcx
	jmp	.LBB2_133
	.p2align	4, 0x90
.LBB2_131:                              #   in Loop: Header=BB2_130 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rcx
	addss	xmm2, xmm2
.LBB2_133:                              # %select.unfold.i.i.i.i54
                                        #   in Loop: Header=BB2_130 Depth=1
	mulss	xmm2, xmm1
	addss	xmm0, xmm2
	movss	dword ptr [rsp + 188], xmm1
	fld	st(0)
	fmul	dword ptr [rsp + 188]
	fstp	dword ptr [rsp + 184]
	movss	xmm1, dword ptr [rsp + 184] # xmm1 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB2_135
# %bb.134:                              #   in Loop: Header=BB2_130 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rdx
	addss	xmm2, xmm2
	jmp	.LBB2_136
.LBB2_127:                              # %.unr-lcssa
	fstp	st(0)
	divss	xmm0, xmm1
	movaps	xmm1, xmmword ptr [rsp + 368] # 16-byte Reload
	addss	xmm1, xmm3
	movaps	xmm3, xmm1
	movaps	xmm1, xmmword ptr [rsp + 352] # 16-byte Reload
	addss	xmm1, xmm4
	movaps	xmm11, xmm1
	movaps	xmm1, xmmword ptr [rsp + 336] # 16-byte Reload
	addss	xmm1, xmm5
	movaps	xmm9, xmm1
	movaps	xmm1, xmmword ptr [rsp + 320] # 16-byte Reload
	addss	xmm1, xmm6
	movaps	xmm6, xmm1
	movaps	xmm1, xmmword ptr [rsp + 304] # 16-byte Reload
	addss	xmm1, xmm7
	movaps	xmm7, xmm1
	movaps	xmm5, xmmword ptr [rsp + 144] # 16-byte Reload
	addss	xmm5, xmm8
	movaps	xmm4, xmmword ptr [rsp + 384] # 16-byte Reload
	addss	xmm4, xmm10
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI2_3]
	jae	.LBB2_128
.LBB2_129:                              # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit56
	movss	xmm1, dword ptr [rip + _ZL4dist.0.1] # xmm1 = mem[0],zero,zero,zero
	movss	xmm2, dword ptr [rip + _ZL4dist.0.0] # xmm2 = mem[0],zero,zero,zero
	subss	xmm1, xmm2
	mulss	xmm1, xmm0
	addss	xmm1, xmm2
	insertps	xmm1, xmm7, 16  # xmm1 = xmm1[0],xmm7[0],xmm1[2,3]
	insertps	xmm1, xmm5, 32  # xmm1 = xmm1[0,1],xmm5[0],xmm1[3]
	insertps	xmm1, xmm4, 48  # xmm1 = xmm1[0,1,2],xmm4[0]
	insertps	xmm3, xmm11, 16 # xmm3 = xmm3[0],xmm11[0],xmm3[2,3]
	insertps	xmm3, xmm9, 32  # xmm3 = xmm3[0,1],xmm9[0],xmm3[3]
	insertps	xmm3, xmm6, 48  # xmm3 = xmm3[0,1,2],xmm6[0]
	movaps	xmmword ptr [r14], xmm3
	movaps	xmmword ptr [r14 + 16], xmm1
	mov	rax, r14
	add	rsp, 488
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.LBB2_9:
	.cfi_def_cfa_offset 512
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_10
.LBB2_26:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_27
.LBB2_43:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_44
.LBB2_60:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_61
.LBB2_77:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_78
.LBB2_94:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_95
.LBB2_111:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	movaps	xmm7, xmmword ptr [rsp + 144] # 16-byte Reload
	movaps	xmm8, xmmword ptr [rsp + 304] # 16-byte Reload
	movaps	xmm5, xmmword ptr [rsp + 320] # 16-byte Reload
	movaps	xmm4, xmmword ptr [rsp + 336] # 16-byte Reload
	movaps	xmm3, xmmword ptr [rsp + 352] # 16-byte Reload
	movaps	xmm2, xmmword ptr [rsp + 368] # 16-byte Reload
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB2_112
.LBB2_128:
	movss	xmm0, dword ptr [rip + .LCPI2_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	movaps	xmmword ptr [rsp + 368], xmm3 # 16-byte Spill
	movaps	xmmword ptr [rsp + 352], xmm11 # 16-byte Spill
	movaps	xmmword ptr [rsp + 336], xmm9 # 16-byte Spill
	movaps	xmmword ptr [rsp + 320], xmm6 # 16-byte Spill
	movaps	xmmword ptr [rsp + 304], xmm7 # 16-byte Spill
	movaps	xmmword ptr [rsp + 144], xmm5 # 16-byte Spill
	movaps	xmmword ptr [rsp + 384], xmm4 # 16-byte Spill
	call	nextafterf@PLT
	movaps	xmm4, xmmword ptr [rsp + 384] # 16-byte Reload
	movaps	xmm5, xmmword ptr [rsp + 144] # 16-byte Reload
	movaps	xmm7, xmmword ptr [rsp + 304] # 16-byte Reload
	movaps	xmm6, xmmword ptr [rsp + 320] # 16-byte Reload
	movaps	xmm9, xmmword ptr [rsp + 336] # 16-byte Reload
	movaps	xmm11, xmmword ptr [rsp + 352] # 16-byte Reload
	movaps	xmm3, xmmword ptr [rsp + 368] # 16-byte Reload
	jmp	.LBB2_129
.Lfunc_end2:
	.size	_Z12random_motorv, .Lfunc_end2-_Z12random_motorv
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3               # -- Begin function _Z12random_pointv
.LCPI3_0:
	.quad	4746794007240114176     # double 2147483646
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI3_1:
	.long	1073741824              # float 2
.LCPI3_2:
	.long	1593835520              # float 9.22337203E+18
.LCPI3_3:
	.long	1065353216              # float 1
.LCPI3_4:
	.long	1325400064              # float 2.14748365E+9
	.text
	.globl	_Z12random_pointv
	.p2align	4, 0x90
	.type	_Z12random_pointv,@function
_Z12random_pointv:                      # @_Z12random_pointv
	.cfi_startproc
# %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	sub	rsp, 216
	.cfi_def_cfa_offset 240
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	mov	r14, rdi
	fld	qword ptr [rip + .LCPI3_0]
	fld	st(0)
	fstp	tbyte ptr [rsp + 16]    # 10-byte Folded Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 36]    # 10-byte Folded Spill
	fld	dword ptr [rip + .LCPI3_1]
	fld	st(0)
	fstp	tbyte ptr [rsp + 152]   # 10-byte Folded Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 36]    # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	dword ptr [rip + .LCPI3_2]
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fld	st(1)
	fstp	tbyte ptr [rsp + 164]   # 10-byte Folded Spill
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 192]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 192]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	movabs	rbx, 8589934597
	test	dil, 1
	jne	.LBB3_2
# %bb.1:
	xorps	xmm0, xmm0
	movss	xmm2, dword ptr [rip + .LCPI3_3] # xmm2 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB3_12
	jmp	.LBB3_7
.LBB3_2:                                # %select.unfold.i.i.i.i.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB3_3
# %bb.4:                                # %select.unfold.i.i.i.i.prol
	cvtsi2ss	xmm0, rdx
	jmp	.LBB3_5
.LBB3_3:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB3_5:                                # %select.unfold.i.i.i.i.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm2, dword ptr [rip + .LCPI3_4] # xmm2 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB3_12
.LBB3_7:
	movss	xmm2, dword ptr [rip + .LCPI3_4] # xmm2 = mem[0],zero,zero,zero
	jmp	.LBB3_8
	.p2align	4, 0x90
.LBB3_17:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB3_12 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB3_18:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB3_12 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm2
	movss	dword ptr [rsp + 116], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 116]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 112]
	movss	xmm2, dword ptr [rsp + 112] # xmm2 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB3_8
.LBB3_12:                               # %select.unfold.i.i.i.i
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB3_13
# %bb.14:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB3_12 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB3_15
	.p2align	4, 0x90
.LBB3_13:                               #   in Loop: Header=BB3_12 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB3_15:                               # %select.unfold.i.i.i.i
                                        #   in Loop: Header=BB3_12 Depth=1
	mulss	xmm1, xmm2
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 124], xmm2
	fld	st(0)
	fmul	dword ptr [rsp + 124]
	fstp	dword ptr [rsp + 120]
	movss	xmm2, dword ptr [rsp + 120] # xmm2 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB3_17
# %bb.16:                               #   in Loop: Header=BB3_12 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB3_18
.LBB3_8:                                # %.unr-lcssa64
	divss	xmm0, xmm2
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI3_3]
	jae	.LBB3_9
.LBB3_10:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit
	movss	dword ptr [rsp + 32], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.1] # xmm0 = mem[0],zero,zero,zero
	movss	dword ptr [rsp + 36], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 48], xmm0 # 16-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 128]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 152]   # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 128]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 164]   # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 184]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 184]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB3_19
# %bb.11:
	xorps	xmm0, xmm0
	movss	xmm3, dword ptr [rip + .LCPI3_3] # xmm3 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movaps	xmm2, xmmword ptr [rsp + 48] # 16-byte Reload
	cmp	rsi, 2
	jae	.LBB3_29
	jmp	.LBB3_24
.LBB3_19:                               # %select.unfold.i.i.i.i6.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	js	.LBB3_20
# %bb.21:                               # %select.unfold.i.i.i.i6.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB3_22
.LBB3_20:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB3_22:                               # %select.unfold.i.i.i.i6.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movaps	xmm2, xmmword ptr [rsp + 48] # 16-byte Reload
	add	rcx, rax
	add	rdi, -1
	movss	xmm3, dword ptr [rip + .LCPI3_4] # xmm3 = mem[0],zero,zero,zero
	cmp	rsi, 2
	jae	.LBB3_29
.LBB3_24:
	movss	xmm3, dword ptr [rip + .LCPI3_4] # xmm3 = mem[0],zero,zero,zero
	jmp	.LBB3_25
	.p2align	4, 0x90
.LBB3_34:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB3_29 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
.LBB3_35:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB3_29 Depth=1
	add	rcx, rax
	mulss	xmm1, xmm3
	movss	dword ptr [rsp + 100], xmm3
	fld	st(0)
	fmul	dword ptr [rsp + 100]
	addss	xmm0, xmm1
	fstp	dword ptr [rsp + 96]
	movss	xmm3, dword ptr [rsp + 96] # xmm3 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB3_25
.LBB3_29:                               # %select.unfold.i.i.i.i6
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB3_30
# %bb.31:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB3_29 Depth=1
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	jmp	.LBB3_32
	.p2align	4, 0x90
.LBB3_30:                               #   in Loop: Header=BB3_29 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rcx
	addss	xmm1, xmm1
.LBB3_32:                               # %select.unfold.i.i.i.i6
                                        #   in Loop: Header=BB3_29 Depth=1
	mulss	xmm1, xmm3
	addss	xmm0, xmm1
	movss	dword ptr [rsp + 108], xmm3
	fld	st(0)
	fmul	dword ptr [rsp + 108]
	fstp	dword ptr [rsp + 104]
	movss	xmm3, dword ptr [rsp + 104] # xmm3 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB3_34
# %bb.33:                               #   in Loop: Header=BB3_29 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm1, xmm1
	cvtsi2ss	xmm1, rdx
	addss	xmm1, xmm1
	jmp	.LBB3_35
.LBB3_25:                               # %.unr-lcssa60
	divss	xmm0, xmm3
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI3_3]
	jae	.LBB3_26
.LBB3_27:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit8
	movss	dword ptr [rsp + 28], xmm0 # 4-byte Spill
	movss	xmm0, dword ptr [rsp + 36] # 4-byte Reload
                                        # xmm0 = mem[0],zero,zero,zero
	subss	xmm0, xmm2
	movss	dword ptr [rsp + 36], xmm0 # 4-byte Spill
	movss	xmm1, dword ptr [rip + _ZL4dist.0.1] # xmm1 = mem[0],zero,zero,zero
	movss	xmm0, dword ptr [rip + _ZL4dist.0.0] # xmm0 = mem[0],zero,zero,zero
	movaps	xmmword ptr [rsp + 128], xmm0 # 16-byte Spill
	subss	xmm1, xmm0
	movss	dword ptr [rsp + 76], xmm1 # 4-byte Spill
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fstp	tbyte ptr [rsp + 204]   # 10-byte Folded Spill
	fld	tbyte ptr [rsp + 152]   # 10-byte Folded Reload
	fstp	tbyte ptr [rsp]
	call	logl@PLT
	fld	tbyte ptr [rsp + 204]   # 10-byte Folded Reload
	fdivrp	st(1), st
	fld	tbyte ptr [rsp + 164]   # 10-byte Folded Reload
	fld	st(1)
	fsub	st, st(1)
	xor	ecx, ecx
	fxch	st(2)
	fucomi	st, st(1)
	fstp	st(1)
	fxch	st(1)
	fcmovb	st, st(1)
	fstp	st(1)
	fisttp	qword ptr [rsp + 176]
	setae	cl
	shl	rcx, 63
	xor	rcx, qword ptr [rsp + 176]
	lea	rax, [rcx + 23]
	xor	edx, edx
	div	rcx
	mov	rsi, rax
	cmp	rax, 1
	mov	edi, 1
	cmova	rdi, rax
	mov	rcx, qword ptr [rip + _ZL3lcg.0]
	test	dil, 1
	jne	.LBB3_36
# %bb.28:
	xorps	xmm0, xmm0
	movss	xmm1, dword ptr [rip + .LCPI3_3] # xmm1 = mem[0],zero,zero,zero
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movss	xmm3, dword ptr [rsp + 32] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	movss	xmm4, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm4 = mem[0],zero,zero,zero
	jmp	.LBB3_40
.LBB3_36:                               # %select.unfold.i.i.i.i14.prol
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	movss	xmm3, dword ptr [rsp + 32] # 4-byte Reload
                                        # xmm3 = mem[0],zero,zero,zero
	js	.LBB3_37
# %bb.38:                               # %select.unfold.i.i.i.i14.prol
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	jmp	.LBB3_39
.LBB3_37:
	mov	r8, rdx
	shr	r8
	and	edx, 1
	or	rdx, r8
	xorps	xmm0, xmm0
	cvtsi2ss	xmm0, rdx
	addss	xmm0, xmm0
.LBB3_39:                               # %select.unfold.i.i.i.i14.prol
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	movss	xmm4, dword ptr [rsp + 28] # 4-byte Reload
                                        # xmm4 = mem[0],zero,zero,zero
	add	rcx, rax
	add	rdi, -1
	movss	xmm1, dword ptr [rip + .LCPI3_4] # xmm1 = mem[0],zero,zero,zero
.LBB3_40:                               # %select.unfold.i.i.i.i14.prol.loopexit
	mulss	xmm3, dword ptr [rsp + 36] # 4-byte Folded Reload
	mulss	xmm4, dword ptr [rsp + 76] # 4-byte Folded Reload
	cmp	rsi, 2
	jae	.LBB3_45
# %bb.41:
	fstp	st(0)
	movss	xmm1, dword ptr [rip + .LCPI3_4] # xmm1 = mem[0],zero,zero,zero
	fldz
	jmp	.LBB3_42
	.p2align	4, 0x90
.LBB3_50:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB3_45 Depth=1
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rdx
.LBB3_51:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB3_45 Depth=1
	add	rcx, rax
	mulss	xmm2, xmm1
	movss	dword ptr [rsp + 84], xmm1
	fld	st(0)
	fmul	dword ptr [rsp + 84]
	addss	xmm0, xmm2
	fstp	dword ptr [rsp + 80]
	movss	xmm1, dword ptr [rsp + 80] # xmm1 = mem[0],zero,zero,zero
	add	rdi, -2
	je	.LBB3_42
.LBB3_45:                               # %select.unfold.i.i.i.i14
                                        # =>This Inner Loop Header: Depth=1
	imul	rcx, rcx, 48271
	mov	rax, rcx
	mul	rbx
	mov	rsi, rcx
	sub	rsi, rdx
	shr	rsi
	add	rsi, rdx
	shr	rsi, 30
	mov	rax, rsi
	shl	rax, 31
	sub	rsi, rax
	lea	rax, [rcx + rsi]
	add	rcx, rsi
	add	rcx, -1
	test	rcx, rcx
	js	.LBB3_46
# %bb.47:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB3_45 Depth=1
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rcx
	jmp	.LBB3_48
	.p2align	4, 0x90
.LBB3_46:                               #   in Loop: Header=BB3_45 Depth=1
	mov	rdx, rcx
	shr	rdx
	and	ecx, 1
	or	rcx, rdx
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rcx
	addss	xmm2, xmm2
.LBB3_48:                               # %select.unfold.i.i.i.i14
                                        #   in Loop: Header=BB3_45 Depth=1
	mulss	xmm2, xmm1
	addss	xmm0, xmm2
	movss	dword ptr [rsp + 92], xmm1
	fld	st(0)
	fmul	dword ptr [rsp + 92]
	fstp	dword ptr [rsp + 88]
	movss	xmm1, dword ptr [rsp + 88] # xmm1 = mem[0],zero,zero,zero
	imul	rcx, rax, 48271
	mov	rax, rcx
	mul	rbx
	mov	rax, rcx
	sub	rax, rdx
	shr	rax
	add	rax, rdx
	shr	rax, 30
	mov	rdx, rax
	shl	rdx, 31
	sub	rax, rdx
	lea	rdx, [rcx + rax]
	add	rdx, -1
	test	rdx, rdx
	jns	.LBB3_50
# %bb.49:                               #   in Loop: Header=BB3_45 Depth=1
	mov	rsi, rdx
	shr	rsi
	and	edx, 1
	or	rdx, rsi
	xorps	xmm2, xmm2
	cvtsi2ss	xmm2, rdx
	addss	xmm2, xmm2
	jmp	.LBB3_51
.LBB3_42:                               # %.unr-lcssa
	fstp	st(0)
	divss	xmm0, xmm1
	movaps	xmm1, xmmword ptr [rsp + 48] # 16-byte Reload
	addss	xmm1, xmm3
	movaps	xmm3, xmm1
	movaps	xmm1, xmmword ptr [rsp + 128] # 16-byte Reload
	addss	xmm1, xmm4
	movaps	xmm4, xmm1
	mov	qword ptr [rip + _ZL3lcg.0], rcx
	ucomiss	xmm0, dword ptr [rip + .LCPI3_3]
	jae	.LBB3_43
.LBB3_44:                               # %_ZNSt25uniform_real_distributionIfEclISt26linear_congruential_engineImLm48271ELm0ELm2147483647EEEEfRT_.exit16
	movss	xmm1, dword ptr [rip + _ZL4dist.0.1] # xmm1 = mem[0],zero,zero,zero
	movss	xmm2, dword ptr [rip + _ZL4dist.0.0] # xmm2 = mem[0],zero,zero,zero
	subss	xmm1, xmm2
	mulss	xmm1, xmm0
	addss	xmm1, xmm2
	movss	xmm0, dword ptr [rip + .LCPI3_3] # xmm0 = mem[0],zero,zero,zero
	insertps	xmm0, xmm1, 16  # xmm0 = xmm0[0],xmm1[0],xmm0[2,3]
	insertps	xmm0, xmm4, 32  # xmm0 = xmm0[0,1],xmm4[0],xmm0[3]
	insertps	xmm0, xmm3, 48  # xmm0 = xmm0[0,1,2],xmm3[0]
	movaps	xmmword ptr [r14], xmm0
	mov	rax, r14
	add	rsp, 216
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.LBB3_9:
	.cfi_def_cfa_offset 240
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI3_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB3_10
.LBB3_26:
	fstp	st(0)
	movss	xmm0, dword ptr [rip + .LCPI3_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	call	nextafterf@PLT
	movaps	xmm2, xmmword ptr [rsp + 48] # 16-byte Reload
	fld	tbyte ptr [rsp + 16]    # 10-byte Folded Reload
	jmp	.LBB3_27
.LBB3_43:
	movss	xmm0, dword ptr [rip + .LCPI3_3] # xmm0 = mem[0],zero,zero,zero
	xorps	xmm1, xmm1
	movaps	xmmword ptr [rsp + 48], xmm3 # 16-byte Spill
	movaps	xmmword ptr [rsp + 128], xmm4 # 16-byte Spill
	call	nextafterf@PLT
	movaps	xmm4, xmmword ptr [rsp + 128] # 16-byte Reload
	movaps	xmm3, xmmword ptr [rsp + 48] # 16-byte Reload
	jmp	.LBB3_44
.Lfunc_end3:
	.size	_Z12random_pointv, .Lfunc_end3-_Z12random_pointv
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _ZL20BM_rotor_compositionRN9benchmark5StateE
.LCPI4_0:
	.long	1063299392              # float 0.87758255
	.long	3199620054              # float -0.356108367
	.long	3196632800              # float -0.267081261
	.long	3191231446              # float -0.178054184
.LCPI4_1:
	.long	1063299392              # float 0.87758255
	.long	1045840539              # float 0.209238455
	.long	1054229147              # float 0.418476909
	.long	1037451931              # float 0.104619227
	.text
	.p2align	4, 0x90
	.type	_ZL20BM_rotor_compositionRN9benchmark5StateE,@function
_ZL20BM_rotor_compositionRN9benchmark5StateE: # @_ZL20BM_rotor_compositionRN9benchmark5StateE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 48
	.cfi_def_cfa_offset 64
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 40], rax
	mov	al, byte ptr [rip + _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1]
	test	al, al
	je	.LBB4_1
.LBB4_3:
	mov	al, byte ptr [rip + _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2]
	test	al, al
	je	.LBB4_4
.LBB4_6:
	mov	eax, -2147483648
	movd	xmm5, eax
	movdqa	xmmword ptr [rsp], xmm5 # 16-byte Spill
	jmp	.LBB4_7
	.p2align	4, 0x90
.LBB4_11:                               #   in Loop: Header=BB4_7 Depth=1
	add	rax, -1
	mov	qword ptr [rbx], rax
	#APP
	#NO_APP
	movaps	xmm0, xmmword ptr [rip + _ZZL20BM_rotor_compositionRN9benchmark5StateEE2r1.0.0.0.0]
	movaps	xmm1, xmm0
	shufps	xmm1, xmm0, 0           # xmm1 = xmm1[0,0],xmm0[0,0]
	movaps	xmm2, xmmword ptr [rip + _ZZL20BM_rotor_compositionRN9benchmark5StateEE2r2.0.0.0.0]
	mulps	xmm1, xmm2
	movaps	xmm3, xmm0
	shufps	xmm3, xmm0, 157         # xmm3 = xmm3[1,3],xmm0[1,2]
	movaps	xmm4, xmm2
	shufps	xmm4, xmm2, 121         # xmm4 = xmm4[1,2],xmm2[3,1]
	mulps	xmm4, xmm3
	subps	xmm1, xmm4
	movaps	xmm3, xmm0
	shufps	xmm3, xmm0, 230         # xmm3 = xmm3[2,1],xmm0[2,3]
	movaps	xmm4, xmm2
	shufps	xmm4, xmm2, 2           # xmm4 = xmm4[2,0],xmm2[0,0]
	mulps	xmm4, xmm3
	shufps	xmm0, xmm0, 123         # xmm0 = xmm0[3,2,3,1]
	shufps	xmm2, xmm2, 159         # xmm2 = xmm2[3,3,1,2]
	mulps	xmm2, xmm0
	addps	xmm2, xmm4
	xorps	xmm2, xmm5
	addps	xmm2, xmm1
	movaps	xmmword ptr [rsp + 16], xmm2
	#APP
	#NO_APP
.LBB4_7:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB4_11
# %bb.8:                                #   in Loop: Header=BB4_7 Depth=1
	cmp	byte ptr [rbx + 24], 0
	jne	.LBB4_12
# %bb.9:                                #   in Loop: Header=BB4_7 Depth=1
	mov	rdi, rbx
	call	_ZN9benchmark5State16StartKeepRunningEv@PLT
	movdqa	xmm5, xmmword ptr [rsp] # 16-byte Reload
	cmp	byte ptr [rbx + 26], 0
	jne	.LBB4_12
# %bb.10:                               #   in Loop: Header=BB4_7 Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB4_11
.LBB4_12:
	mov	rdi, rbx
	call	_ZN9benchmark5State17FinishKeepRunningEv@PLT
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 40]
	jne	.LBB4_14
# %bb.13:                               # %SP_return
	add	rsp, 48
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB4_1:
	.cfi_def_cfa_offset 64
	lea	rdi, [rip + _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1]
	call	__cxa_guard_acquire@PLT
	test	eax, eax
	je	.LBB4_3
# %bb.2:
	movaps	xmm0, xmmword ptr [rip + .LCPI4_0] # xmm0 = [8.7758255E-1,-3.56108367E-1,-2.67081261E-1,-1.78054184E-1]
	movaps	xmmword ptr [rip + _ZZL20BM_rotor_compositionRN9benchmark5StateEE2r1.0.0.0.0], xmm0
	lea	rdi, [rip + _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1]
	call	__cxa_guard_release@PLT
	jmp	.LBB4_3
.LBB4_4:
	lea	rdi, [rip + _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2]
	call	__cxa_guard_acquire@PLT
	test	eax, eax
	je	.LBB4_6
# %bb.5:
	movaps	xmm0, xmmword ptr [rip + .LCPI4_1] # xmm0 = [8.7758255E-1,2.09238455E-1,4.18476909E-1,1.04619227E-1]
	movaps	xmmword ptr [rip + _ZZL20BM_rotor_compositionRN9benchmark5StateEE2r2.0.0.0.0], xmm0
	lea	rdi, [rip + _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2]
	call	__cxa_guard_release@PLT
	jmp	.LBB4_6
.LBB4_14:                               # %CallStackCheckFailBlk
	call	__stack_chk_fail@PLT
.Lfunc_end4:
	.size	_ZL20BM_rotor_compositionRN9benchmark5StateE, .Lfunc_end4-_ZL20BM_rotor_compositionRN9benchmark5StateE
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _ZL20BM_rotor_applicationRN9benchmark5StateE
.LCPI5_0:
	.long	1065353216              # float 1
	.long	1078126112              # float 3.04529572
	.long	1071386208              # float 1.71918869
	.long	1068126702              # float 1.3306253
	.text
	.p2align	4, 0x90
	.type	_ZL20BM_rotor_applicationRN9benchmark5StateE,@function
_ZL20BM_rotor_applicationRN9benchmark5StateE: # @_ZL20BM_rotor_applicationRN9benchmark5StateE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 32
	.cfi_def_cfa_offset 48
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 24], rax
	movaps	xmm0, xmmword ptr [rip + .LCPI5_0] # xmm0 = [1.0E+0,3.04529572E+0,1.71918869E+0,1.3306253E+0]
	jmp	.LBB5_1
	.p2align	4, 0x90
.LBB5_5:                                #   in Loop: Header=BB5_1 Depth=1
	add	rax, -1
	mov	qword ptr [rbx], rax
	#APP
	#NO_APP
	movaps	xmmword ptr [rsp], xmm0
	#APP
	#NO_APP
.LBB5_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB5_5
# %bb.2:                                #   in Loop: Header=BB5_1 Depth=1
	cmp	byte ptr [rbx + 24], 0
	jne	.LBB5_6
# %bb.3:                                #   in Loop: Header=BB5_1 Depth=1
	mov	rdi, rbx
	call	_ZN9benchmark5State16StartKeepRunningEv@PLT
	movaps	xmm0, xmmword ptr [rip + .LCPI5_0] # xmm0 = [1.0E+0,3.04529572E+0,1.71918869E+0,1.3306253E+0]
	cmp	byte ptr [rbx + 26], 0
	jne	.LBB5_6
# %bb.4:                                #   in Loop: Header=BB5_1 Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB5_5
.LBB5_6:
	mov	rdi, rbx
	call	_ZN9benchmark5State17FinishKeepRunningEv@PLT
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 24]
	jne	.LBB5_8
# %bb.7:                                # %SP_return
	add	rsp, 32
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB5_8:                                # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 48
	call	__stack_chk_fail@PLT
.Lfunc_end5:
	.size	_ZL20BM_rotor_applicationRN9benchmark5StateE, .Lfunc_end5-_ZL20BM_rotor_applicationRN9benchmark5StateE
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _ZL26BM_rotor_matrix_conversionRN9benchmark5StateE
.LCPI6_0:
	.long	1058704554              # float 0.603708863
	.long	1060657925              # float 0.720138847
	.long	3199145264              # float -0.341958523
	.long	2147483648              # float -0
.LCPI6_1:
	.long	3204950215              # float -0.529919088
	.long	1060034286              # float 0.682967067
	.long	1057010481              # float 0.502734244
	.long	0                       # float 0
.LCPI6_2:
	.long	1058568256              # float 0.595584869
	.long	3187307946              # float -0.122294739
	.long	1061895912              # float 0.793928623
	.long	0                       # float 0
.LCPI6_3:
	.long	0                       # float 0
	.long	0                       # float 0
	.long	0                       # float 0
	.long	1065353216              # float 1
	.text
	.p2align	4, 0x90
	.type	_ZL26BM_rotor_matrix_conversionRN9benchmark5StateE,@function
_ZL26BM_rotor_matrix_conversionRN9benchmark5StateE: # @_ZL26BM_rotor_matrix_conversionRN9benchmark5StateE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 80
	.cfi_def_cfa_offset 96
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 72], rax
	movaps	xmm0, xmmword ptr [rip + .LCPI6_0] # xmm0 = [6.03708863E-1,7.20138847E-1,-3.41958523E-1,-0.0E+0]
	movaps	xmm1, xmmword ptr [rip + .LCPI6_1] # xmm1 = [-5.29919088E-1,6.82967067E-1,5.02734244E-1,0.0E+0]
	movaps	xmm2, xmmword ptr [rip + .LCPI6_2] # xmm2 = [5.95584869E-1,-1.22294739E-1,7.93928623E-1,0.0E+0]
	movaps	xmm3, xmmword ptr [rip + .LCPI6_3] # xmm3 = [0.0E+0,0.0E+0,0.0E+0,1.0E+0]
	jmp	.LBB6_1
	.p2align	4, 0x90
.LBB6_5:                                #   in Loop: Header=BB6_1 Depth=1
	add	rax, -1
	mov	qword ptr [rbx], rax
	#APP
	#NO_APP
	movaps	xmmword ptr [rsp], xmm0
	movaps	xmmword ptr [rsp + 16], xmm1
	movaps	xmmword ptr [rsp + 32], xmm2
	movaps	xmmword ptr [rsp + 48], xmm3
	#APP
	#NO_APP
.LBB6_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB6_5
# %bb.2:                                #   in Loop: Header=BB6_1 Depth=1
	cmp	byte ptr [rbx + 24], 0
	jne	.LBB6_6
# %bb.3:                                #   in Loop: Header=BB6_1 Depth=1
	mov	rdi, rbx
	call	_ZN9benchmark5State16StartKeepRunningEv@PLT
	movaps	xmm3, xmmword ptr [rip + .LCPI6_3] # xmm3 = [0.0E+0,0.0E+0,0.0E+0,1.0E+0]
	movaps	xmm2, xmmword ptr [rip + .LCPI6_2] # xmm2 = [5.95584869E-1,-1.22294739E-1,7.93928623E-1,0.0E+0]
	movaps	xmm1, xmmword ptr [rip + .LCPI6_1] # xmm1 = [-5.29919088E-1,6.82967067E-1,5.02734244E-1,0.0E+0]
	movaps	xmm0, xmmword ptr [rip + .LCPI6_0] # xmm0 = [6.03708863E-1,7.20138847E-1,-3.41958523E-1,-0.0E+0]
	cmp	byte ptr [rbx + 26], 0
	jne	.LBB6_6
# %bb.4:                                #   in Loop: Header=BB6_1 Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB6_5
.LBB6_6:
	mov	rdi, rbx
	call	_ZN9benchmark5State17FinishKeepRunningEv@PLT
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 72]
	jne	.LBB6_8
# %bb.7:                                # %SP_return
	add	rsp, 80
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB6_8:                                # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 96
	call	__stack_chk_fail@PLT
.Lfunc_end6:
	.size	_ZL26BM_rotor_matrix_conversionRN9benchmark5StateE, .Lfunc_end6-_ZL26BM_rotor_matrix_conversionRN9benchmark5StateE
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _ZL20BM_motor_compositionRN9benchmark5StateE
.LCPI7_0:
	.long	3246391296              # float -16
	.long	3225419776              # float -3
	.long	3238002688              # float -8
	.long	1100480512              # float 19
.LCPI7_1:
	.long	1110966272              # float 46
	.long	1111228416              # float 47
	.long	3251634176              # float -26
	.long	1113325568              # float 55
	.text
	.p2align	4, 0x90
	.type	_ZL20BM_motor_compositionRN9benchmark5StateE,@function
_ZL20BM_motor_compositionRN9benchmark5StateE: # @_ZL20BM_motor_compositionRN9benchmark5StateE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 48
	.cfi_def_cfa_offset 64
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 40], rax
	movaps	xmm0, xmmword ptr [rip + .LCPI7_0] # xmm0 = [-1.6E+1,-3.0E+0,-8.0E+0,1.9E+1]
	movaps	xmm1, xmmword ptr [rip + .LCPI7_1] # xmm1 = [4.6E+1,4.7E+1,-2.6E+1,5.5E+1]
	jmp	.LBB7_1
	.p2align	4, 0x90
.LBB7_5:                                #   in Loop: Header=BB7_1 Depth=1
	add	rax, -1
	mov	qword ptr [rbx], rax
	#APP
	#NO_APP
	movaps	xmmword ptr [rsp], xmm0
	movaps	xmmword ptr [rsp + 16], xmm1
	#APP
	#NO_APP
.LBB7_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB7_5
# %bb.2:                                #   in Loop: Header=BB7_1 Depth=1
	cmp	byte ptr [rbx + 24], 0
	jne	.LBB7_6
# %bb.3:                                #   in Loop: Header=BB7_1 Depth=1
	mov	rdi, rbx
	call	_ZN9benchmark5State16StartKeepRunningEv@PLT
	movaps	xmm1, xmmword ptr [rip + .LCPI7_1] # xmm1 = [4.6E+1,4.7E+1,-2.6E+1,5.5E+1]
	movaps	xmm0, xmmword ptr [rip + .LCPI7_0] # xmm0 = [-1.6E+1,-3.0E+0,-8.0E+0,1.9E+1]
	cmp	byte ptr [rbx + 26], 0
	jne	.LBB7_6
# %bb.4:                                #   in Loop: Header=BB7_1 Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB7_5
.LBB7_6:
	mov	rdi, rbx
	call	_ZN9benchmark5State17FinishKeepRunningEv@PLT
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 40]
	jne	.LBB7_8
# %bb.7:                                # %SP_return
	add	rsp, 48
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB7_8:                                # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 64
	call	__stack_chk_fail@PLT
.Lfunc_end7:
	.size	_ZL20BM_motor_compositionRN9benchmark5StateE, .Lfunc_end7-_ZL20BM_motor_compositionRN9benchmark5StateE
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _ZL20BM_motor_applicationRN9benchmark5StateE
.LCPI8_0:
	.long	1106247680              # float 30
	.long	3261595648              # float -58
	.long	3255828480              # float -36
	.long	1107820544              # float 34
	.text
	.p2align	4, 0x90
	.type	_ZL20BM_motor_applicationRN9benchmark5StateE,@function
_ZL20BM_motor_applicationRN9benchmark5StateE: # @_ZL20BM_motor_applicationRN9benchmark5StateE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 32
	.cfi_def_cfa_offset 48
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 24], rax
	movaps	xmm0, xmmword ptr [rip + .LCPI8_0] # xmm0 = [3.0E+1,-5.8E+1,-3.6E+1,3.4E+1]
	jmp	.LBB8_1
	.p2align	4, 0x90
.LBB8_5:                                #   in Loop: Header=BB8_1 Depth=1
	add	rax, -1
	mov	qword ptr [rbx], rax
	#APP
	#NO_APP
	movaps	xmmword ptr [rsp], xmm0
	#APP
	#NO_APP
.LBB8_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB8_5
# %bb.2:                                #   in Loop: Header=BB8_1 Depth=1
	cmp	byte ptr [rbx + 24], 0
	jne	.LBB8_6
# %bb.3:                                #   in Loop: Header=BB8_1 Depth=1
	mov	rdi, rbx
	call	_ZN9benchmark5State16StartKeepRunningEv@PLT
	movaps	xmm0, xmmword ptr [rip + .LCPI8_0] # xmm0 = [3.0E+1,-5.8E+1,-3.6E+1,3.4E+1]
	cmp	byte ptr [rbx + 26], 0
	jne	.LBB8_6
# %bb.4:                                #   in Loop: Header=BB8_1 Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB8_5
.LBB8_6:
	mov	rdi, rbx
	call	_ZN9benchmark5State17FinishKeepRunningEv@PLT
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 24]
	jne	.LBB8_8
# %bb.7:                                # %SP_return
	add	rsp, 32
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB8_8:                                # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 48
	call	__stack_chk_fail@PLT
.Lfunc_end8:
	.size	_ZL20BM_motor_applicationRN9benchmark5StateE, .Lfunc_end8-_ZL20BM_motor_applicationRN9benchmark5StateE
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _ZL26BM_motor_matrix_conversionRN9benchmark5StateE
.LCPI9_0:
	.long	1082130432              # float 4
	.long	1101004800              # float 20
	.long	1102053376              # float 22
	.long	0                       # float 0
.LCPI9_1:
	.long	1105199104              # float 28
	.long	3240099840              # float -10
	.long	1082130432              # float 4
	.long	0                       # float 0
.LCPI9_2:
	.long	1092616192              # float 10
	.long	1101004800              # float 20
	.long	3248488448              # float -20
	.long	0                       # float 0
.LCPI9_3:
	.long	3261071360              # float -56
	.long	3267362816              # float -96
	.long	3252682752              # float -28
	.long	1106247680              # float 30
	.text
	.p2align	4, 0x90
	.type	_ZL26BM_motor_matrix_conversionRN9benchmark5StateE,@function
_ZL26BM_motor_matrix_conversionRN9benchmark5StateE: # @_ZL26BM_motor_matrix_conversionRN9benchmark5StateE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 80
	.cfi_def_cfa_offset 96
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 72], rax
	movaps	xmm0, xmmword ptr [rip + .LCPI9_0] # xmm0 = [4.0E+0,2.0E+1,2.2E+1,0.0E+0]
	movaps	xmm1, xmmword ptr [rip + .LCPI9_1] # xmm1 = [2.8E+1,-1.0E+1,4.0E+0,0.0E+0]
	movaps	xmm2, xmmword ptr [rip + .LCPI9_2] # xmm2 = [1.0E+1,2.0E+1,-2.0E+1,0.0E+0]
	movaps	xmm3, xmmword ptr [rip + .LCPI9_3] # xmm3 = [-5.6E+1,-9.6E+1,-2.8E+1,3.0E+1]
	jmp	.LBB9_1
	.p2align	4, 0x90
.LBB9_5:                                #   in Loop: Header=BB9_1 Depth=1
	add	rax, -1
	mov	qword ptr [rbx], rax
	#APP
	#NO_APP
	movaps	xmmword ptr [rsp], xmm0
	movaps	xmmword ptr [rsp + 16], xmm1
	movaps	xmmword ptr [rsp + 32], xmm2
	movaps	xmmword ptr [rsp + 48], xmm3
	#APP
	#NO_APP
.LBB9_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB9_5
# %bb.2:                                #   in Loop: Header=BB9_1 Depth=1
	cmp	byte ptr [rbx + 24], 0
	jne	.LBB9_6
# %bb.3:                                #   in Loop: Header=BB9_1 Depth=1
	mov	rdi, rbx
	call	_ZN9benchmark5State16StartKeepRunningEv@PLT
	movaps	xmm3, xmmword ptr [rip + .LCPI9_3] # xmm3 = [-5.6E+1,-9.6E+1,-2.8E+1,3.0E+1]
	movaps	xmm2, xmmword ptr [rip + .LCPI9_2] # xmm2 = [1.0E+1,2.0E+1,-2.0E+1,0.0E+0]
	movaps	xmm1, xmmword ptr [rip + .LCPI9_1] # xmm1 = [2.8E+1,-1.0E+1,4.0E+0,0.0E+0]
	movaps	xmm0, xmmword ptr [rip + .LCPI9_0] # xmm0 = [4.0E+0,2.0E+1,2.2E+1,0.0E+0]
	cmp	byte ptr [rbx + 26], 0
	jne	.LBB9_6
# %bb.4:                                #   in Loop: Header=BB9_1 Depth=1
	mov	rax, qword ptr [rbx]
	test	rax, rax
	jne	.LBB9_5
.LBB9_6:
	mov	rdi, rbx
	call	_ZN9benchmark5State17FinishKeepRunningEv@PLT
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 72]
	jne	.LBB9_8
# %bb.7:                                # %SP_return
	add	rsp, 80
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB9_8:                                # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 96
	call	__stack_chk_fail@PLT
.Lfunc_end9:
	.size	_ZL26BM_motor_matrix_conversionRN9benchmark5StateE, .Lfunc_end9-_ZL26BM_motor_matrix_conversionRN9benchmark5StateE
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	sub	rsp, 16
	.cfi_def_cfa_offset 32
	.cfi_offset rbx, -16
	mov	rbx, rsi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 8], rax
	mov	dword ptr [rsp + 4], edi
	lea	rdi, [rsp + 4]
	call	_ZN9benchmark10InitializeEPiPPc@PLT
	mov	edi, dword ptr [rsp + 4]
	mov	rsi, rbx
	call	_ZN9benchmark27ReportUnrecognizedArgumentsEiPPc@PLT
	mov	ecx, eax
	mov	eax, 1
	test	cl, cl
	jne	.LBB10_2
# %bb.1:
	call	_ZN9benchmark22RunSpecifiedBenchmarksEv@PLT
	xor	eax, eax
.LBB10_2:
	mov	rcx, qword ptr fs:[40]
	cmp	rcx, qword ptr [rsp + 8]
	jne	.LBB10_4
# %bb.3:                                # %SP_return
	add	rsp, 16
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.LBB10_4:                               # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 32
	call	__stack_chk_fail@PLT
.Lfunc_end10:
	.size	main, .Lfunc_end10-main
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_bench.cpp
	.type	_GLOBAL__sub_I_bench.cpp,@function
_GLOBAL__sub_I_bench.cpp:               # @_GLOBAL__sub_I_bench.cpp
	.cfi_startproc
# %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	sub	rsp, 40
	.cfi_def_cfa_offset 64
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 32], rax
	call	_ZN9benchmark8internal17InitializeStreamsEv@PLT
	lea	rbx, [rsp + 16]
	mov	qword ptr [rsp], rbx
	mov	dword ptr [rsp + 16], 1634100580
	mov	dword ptr [rsp + 19], 1953264993
	mov	qword ptr [rsp + 8], 7
	mov	byte ptr [rsp + 23], 0
	lea	rdi, [rip + _ZL1r]
	mov	rsi, rsp
	call	_ZNSt13random_device7_M_initERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE@PLT
	mov	rdi, qword ptr [rsp]
	cmp	rdi, rbx
	je	.LBB11_2
# %bb.1:
	call	_ZdlPv@PLT
.LBB11_2:                               # %__cxx_global_var_init.1.exit
	lea	rdi, [rip + _ZNSt13random_deviceD2Ev]
	lea	rbx, [rip + _ZL1r]
	lea	rdx, [rip + __dso_handle]
	mov	rsi, rbx
	call	__cxa_atexit@PLT
	mov	rdi, rbx
	call	_ZNSt13random_device9_M_getvalEv@PLT
	mov	ecx, eax
	lea	rcx, [rcx + 2*rcx]
	shr	rcx, 32
	mov	edx, eax
	sub	edx, ecx
	shr	edx
	add	edx, ecx
	shr	edx, 30
	mov	ecx, edx
	shl	ecx, 31
	sub	edx, ecx
	add	edx, eax
	mov	eax, 1
	cmovne	eax, edx
	mov	qword ptr [rip + _ZL3lcg.0], rax
	mov	dword ptr [rip + _ZL4dist.0.0], -1027080192
	mov	dword ptr [rip + _ZL4dist.0.1], 1120403456
	mov	edi, 200
	call	_Znwm@PLT
	mov	rbx, rax
	lea	rsi, [rip + .L.str]
	mov	rdi, rax
	call	_ZN9benchmark8internal9BenchmarkC2EPKc@PLT
	mov	r14, qword ptr [rip + _ZTVN9benchmark8internal17FunctionBenchmarkE@GOTPCREL]
	add	r14, 16
	mov	qword ptr [rbx], r14
	lea	rax, [rip + _ZL20BM_rotor_compositionRN9benchmark5StateE]
	mov	qword ptr [rbx + 192], rax
	mov	rdi, rbx
	call	_ZN9benchmark8internal25RegisterBenchmarkInternalEPNS0_9BenchmarkE@PLT
	mov	qword ptr [rip + _ZL32_benchmark_2BM_rotor_composition], rax
	mov	edi, 200
	call	_Znwm@PLT
	mov	rbx, rax
	lea	rsi, [rip + .L.str.6]
	mov	rdi, rax
	call	_ZN9benchmark8internal9BenchmarkC2EPKc@PLT
	mov	qword ptr [rbx], r14
	lea	rax, [rip + _ZL20BM_rotor_applicationRN9benchmark5StateE]
	mov	qword ptr [rbx + 192], rax
	mov	rdi, rbx
	call	_ZN9benchmark8internal25RegisterBenchmarkInternalEPNS0_9BenchmarkE@PLT
	mov	qword ptr [rip + _ZL32_benchmark_3BM_rotor_application], rax
	mov	edi, 200
	call	_Znwm@PLT
	mov	rbx, rax
	lea	rsi, [rip + .L.str.8]
	mov	rdi, rax
	call	_ZN9benchmark8internal9BenchmarkC2EPKc@PLT
	mov	qword ptr [rbx], r14
	lea	rax, [rip + _ZL26BM_rotor_matrix_conversionRN9benchmark5StateE]
	mov	qword ptr [rbx + 192], rax
	mov	rdi, rbx
	call	_ZN9benchmark8internal25RegisterBenchmarkInternalEPNS0_9BenchmarkE@PLT
	mov	qword ptr [rip + _ZL38_benchmark_4BM_rotor_matrix_conversion], rax
	mov	edi, 200
	call	_Znwm@PLT
	mov	rbx, rax
	lea	rsi, [rip + .L.str.10]
	mov	rdi, rax
	call	_ZN9benchmark8internal9BenchmarkC2EPKc@PLT
	mov	qword ptr [rbx], r14
	lea	rax, [rip + _ZL20BM_motor_compositionRN9benchmark5StateE]
	mov	qword ptr [rbx + 192], rax
	mov	rdi, rbx
	call	_ZN9benchmark8internal25RegisterBenchmarkInternalEPNS0_9BenchmarkE@PLT
	mov	qword ptr [rip + _ZL32_benchmark_5BM_motor_composition], rax
	mov	edi, 200
	call	_Znwm@PLT
	mov	rbx, rax
	lea	rsi, [rip + .L.str.12]
	mov	rdi, rax
	call	_ZN9benchmark8internal9BenchmarkC2EPKc@PLT
	mov	qword ptr [rbx], r14
	lea	rax, [rip + _ZL20BM_motor_applicationRN9benchmark5StateE]
	mov	qword ptr [rbx + 192], rax
	mov	rdi, rbx
	call	_ZN9benchmark8internal25RegisterBenchmarkInternalEPNS0_9BenchmarkE@PLT
	mov	qword ptr [rip + _ZL32_benchmark_6BM_motor_application], rax
	mov	edi, 200
	call	_Znwm@PLT
	mov	rbx, rax
	lea	rsi, [rip + .L.str.14]
	mov	rdi, rax
	call	_ZN9benchmark8internal9BenchmarkC2EPKc@PLT
	mov	qword ptr [rbx], r14
	lea	rax, [rip + _ZL26BM_motor_matrix_conversionRN9benchmark5StateE]
	mov	qword ptr [rbx + 192], rax
	mov	rdi, rbx
	call	_ZN9benchmark8internal25RegisterBenchmarkInternalEPNS0_9BenchmarkE@PLT
	mov	qword ptr [rip + _ZL38_benchmark_7BM_motor_matrix_conversion], rax
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 32]
	jne	.LBB11_4
# %bb.3:                                # %SP_return
	add	rsp, 40
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.LBB11_4:                               # %CallStackCheckFailBlk
	.cfi_def_cfa_offset 64
	call	__stack_chk_fail@PLT
.Lfunc_end11:
	.size	_GLOBAL__sub_I_bench.cpp, .Lfunc_end11-_GLOBAL__sub_I_bench.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZL1r,@object           # @_ZL1r
	.local	_ZL1r
	.comm	_ZL1r,5000,8
	.hidden	__dso_handle
	.type	_ZL32_benchmark_2BM_rotor_composition,@object # @_ZL32_benchmark_2BM_rotor_composition
	.local	_ZL32_benchmark_2BM_rotor_composition
	.comm	_ZL32_benchmark_2BM_rotor_composition,8,8
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"BM_rotor_composition"
	.size	.L.str, 21

	.type	_ZL32_benchmark_3BM_rotor_application,@object # @_ZL32_benchmark_3BM_rotor_application
	.local	_ZL32_benchmark_3BM_rotor_application
	.comm	_ZL32_benchmark_3BM_rotor_application,8,8
	.type	.L.str.6,@object        # @.str.6
.L.str.6:
	.asciz	"BM_rotor_application"
	.size	.L.str.6, 21

	.type	_ZL38_benchmark_4BM_rotor_matrix_conversion,@object # @_ZL38_benchmark_4BM_rotor_matrix_conversion
	.local	_ZL38_benchmark_4BM_rotor_matrix_conversion
	.comm	_ZL38_benchmark_4BM_rotor_matrix_conversion,8,8
	.type	.L.str.8,@object        # @.str.8
.L.str.8:
	.asciz	"BM_rotor_matrix_conversion"
	.size	.L.str.8, 27

	.type	_ZL32_benchmark_5BM_motor_composition,@object # @_ZL32_benchmark_5BM_motor_composition
	.local	_ZL32_benchmark_5BM_motor_composition
	.comm	_ZL32_benchmark_5BM_motor_composition,8,8
	.type	.L.str.10,@object       # @.str.10
.L.str.10:
	.asciz	"BM_motor_composition"
	.size	.L.str.10, 21

	.type	_ZL32_benchmark_6BM_motor_application,@object # @_ZL32_benchmark_6BM_motor_application
	.local	_ZL32_benchmark_6BM_motor_application
	.comm	_ZL32_benchmark_6BM_motor_application,8,8
	.type	.L.str.12,@object       # @.str.12
.L.str.12:
	.asciz	"BM_motor_application"
	.size	.L.str.12, 21

	.type	_ZL38_benchmark_7BM_motor_matrix_conversion,@object # @_ZL38_benchmark_7BM_motor_matrix_conversion
	.local	_ZL38_benchmark_7BM_motor_matrix_conversion
	.comm	_ZL38_benchmark_7BM_motor_matrix_conversion,8,8
	.type	.L.str.14,@object       # @.str.14
.L.str.14:
	.asciz	"BM_motor_matrix_conversion"
	.size	.L.str.14, 27

	.type	.L.str.15,@object       # @.str.15
.L.str.15:
	.asciz	"default"
	.size	.L.str.15, 8

	.type	_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1,@object # @_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1
	.local	_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1
	.comm	_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1,8,8
	.type	_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2,@object # @_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2
	.local	_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2
	.comm	_ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2,8,8
	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_bench.cpp
	.type	_ZL3lcg.0,@object       # @_ZL3lcg.0
	.local	_ZL3lcg.0
	.comm	_ZL3lcg.0,8,8
	.type	_ZL4dist.0.0,@object    # @_ZL4dist.0.0
	.local	_ZL4dist.0.0
	.comm	_ZL4dist.0.0,4,4
	.type	_ZL4dist.0.1,@object    # @_ZL4dist.0.1
	.local	_ZL4dist.0.1
	.comm	_ZL4dist.0.1,4,4
	.type	_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r1.0.0.0.0,@object # @_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r1.0.0.0.0
	.local	_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r1.0.0.0.0
	.comm	_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r1.0.0.0.0,16,16
	.type	_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r2.0.0.0.0,@object # @_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r2.0.0.0.0
	.local	_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r2.0.0.0.0
	.comm	_ZZL20BM_rotor_compositionRN9benchmark5StateEE2r2.0.0.0.0,16,16

	.ident	"clang version 9.0.1 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym _ZL20BM_rotor_compositionRN9benchmark5StateE
	.addrsig_sym _ZL20BM_rotor_applicationRN9benchmark5StateE
	.addrsig_sym _ZL26BM_rotor_matrix_conversionRN9benchmark5StateE
	.addrsig_sym _ZL20BM_motor_compositionRN9benchmark5StateE
	.addrsig_sym _ZL20BM_motor_applicationRN9benchmark5StateE
	.addrsig_sym _ZL26BM_motor_matrix_conversionRN9benchmark5StateE
	.addrsig_sym _GLOBAL__sub_I_bench.cpp
	.addrsig_sym __stack_chk_fail
	.addrsig_sym _ZL1r
	.addrsig_sym __dso_handle
	.addrsig_sym _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r1
	.addrsig_sym _ZGVZL20BM_rotor_compositionRN9benchmark5StateEE2r2
