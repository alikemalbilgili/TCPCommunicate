	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 3
	.globl	_func                           ; -- Begin function func
	.p2align	2
_func:                                  ; @func
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #144
	.cfi_def_cfa_offset 144
	stp	x29, x30, [sp, #128]            ; 16-byte Folded Spill
	add	x29, sp, #128
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	str	w0, [sp, #36]
	b	LBB0_1
LBB0_1:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_2 Depth 2
	add	x0, sp, #40
	mov	w1, #0
	mov	x2, #80
	bl	_memset
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	str	wzr, [sp, #32]
	b	LBB0_2
LBB0_2:                                 ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	bl	_getchar
	ldrsw	x9, [sp, #32]
	mov	x8, x9
	add	w8, w8, #1
	str	w8, [sp, #32]
	add	x8, sp, #40
	strb	w0, [x8, x9]
	sxtb	w8, w0
	subs	w8, w8, #10
	cset	w8, eq
	tbnz	w8, #0, LBB0_4
	b	LBB0_3
LBB0_3:                                 ;   in Loop: Header=BB0_2 Depth=2
	b	LBB0_2
LBB0_4:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w0, [sp, #36]
	add	x1, sp, #40
	str	x1, [sp, #24]                   ; 8-byte Folded Spill
	mov	x2, #80
	str	x2, [sp, #16]                   ; 8-byte Folded Spill
	bl	_write
	ldr	x2, [sp, #16]                   ; 8-byte Folded Reload
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	mov	w1, #0
	bl	_memset
	ldr	x2, [sp, #16]                   ; 8-byte Folded Reload
	ldr	x1, [sp, #24]                   ; 8-byte Folded Reload
	ldr	w0, [sp, #36]
	bl	_read
	ldr	x8, [sp, #24]                   ; 8-byte Folded Reload
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	adrp	x1, l_.str.2@PAGE
	add	x1, x1, l_.str.2@PAGEOFF
	mov	x2, #4
	bl	_strncmp
	subs	w8, w0, #0
	cset	w8, ne
	tbnz	w8, #0, LBB0_6
	b	LBB0_5
LBB0_5:
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	b	LBB0_7
LBB0_6:                                 ;   in Loop: Header=BB0_1 Depth=1
	b	LBB0_1
LBB0_7:
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB0_9
	b	LBB0_8
LBB0_8:
	bl	___stack_chk_fail
LBB0_9:
	ldp	x29, x30, [sp, #128]            ; 16-byte Folded Reload
	add	sp, sp, #144
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	mov	w0, #2
	mov	w1, #1
	mov	w2, #0
	bl	_socket
	str	w0, [sp, #20]
	ldr	w8, [sp, #20]
	adds	w8, w8, #1
	cset	w8, ne
	tbnz	w8, #0, LBB1_2
	b	LBB1_1
LBB1_1:
	adrp	x0, l_.str.4@PAGE
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	mov	w0, #0
	bl	_exit
LBB1_2:
	adrp	x0, l_.str.5@PAGE
	add	x0, x0, l_.str.5@PAGEOFF
	bl	_printf
	b	LBB1_3
LBB1_3:
	sub	x8, x29, #24
	str	x8, [sp, #8]                    ; 8-byte Folded Spill
	stur	xzr, [x29, #-24]
	stur	xzr, [x29, #-16]
	mov	w8, #2
	sturb	w8, [x29, #-23]
	adrp	x0, l_.str.6@PAGE
	add	x0, x0, l_.str.6@PAGEOFF
	bl	_inet_addr
	ldr	x1, [sp, #8]                    ; 8-byte Folded Reload
	stur	w0, [x29, #-20]
	mov	w8, #36895
	sturh	w8, [x29, #-22]
	ldr	w0, [sp, #20]
	mov	w2, #16
	bl	_connect
	subs	w8, w0, #0
	cset	w8, eq
	tbnz	w8, #0, LBB1_5
	b	LBB1_4
LBB1_4:
	adrp	x0, l_.str.7@PAGE
	add	x0, x0, l_.str.7@PAGEOFF
	bl	_printf
	mov	w0, #0
	bl	_exit
LBB1_5:
	adrp	x0, l_.str.8@PAGE
	add	x0, x0, l_.str.8@PAGEOFF
	bl	_printf
	b	LBB1_6
LBB1_6:
	ldr	w0, [sp, #20]
	bl	_func
	ldr	w0, [sp, #20]
	bl	_close
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB1_8
	b	LBB1_7
LBB1_7:
	bl	___stack_chk_fail
LBB1_8:
	mov	w0, #0
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Enter the string : "

l_.str.1:                               ; @.str.1
	.asciz	"From Server : %s"

l_.str.2:                               ; @.str.2
	.asciz	"exit"

l_.str.3:                               ; @.str.3
	.asciz	"Client Exit...\n"

l_.str.4:                               ; @.str.4
	.asciz	"socket creation failed...\n"

l_.str.5:                               ; @.str.5
	.asciz	"Socket successfully created..\n"

l_.str.6:                               ; @.str.6
	.asciz	"127.0.0.1"

l_.str.7:                               ; @.str.7
	.asciz	"connection with the server failed...\n"

l_.str.8:                               ; @.str.8
	.asciz	"connected to the server..\n"

.subsections_via_symbols
