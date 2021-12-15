	.file	"Acceuil_Actions.c"
	.text
	.section	.rodata
.LC0:
	.string	" "
.LC1:
	.string	"!help"
.LC2:
	.string	"!back"
.LC3:
	.string	"!exit"
.LC4:
	.string	"Action inexistante"
	.text
	.globl	menu_Acceuil
	.type	menu_Acceuil, @function
menu_Acceuil:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movq	%rdi, -168(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
.L6:
	movq	stdin(%rip), %rdx
	leaq	-144(%rbp), %rax
	movl	$127, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -156(%rbp)
	movl	-156(%rbp), %eax
	subl	$1, %eax
	cltq
	movb	$32, -144(%rbp,%rax)
	movl	-156(%rbp), %eax
	cltq
	movb	$0, -144(%rbp,%rax)
	leaq	-144(%rbp), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L6
	movq	-152(%rbp), %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L3
	movl	$1, %eax
	jmp	.L7
.L3:
	movq	-152(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L5
	movl	$0, %eax
	jmp	.L7
.L5:
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	jmp	.L6
.L7:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L8
	call	__stack_chk_fail@PLT
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	menu_Acceuil, .-menu_Acceuil
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
