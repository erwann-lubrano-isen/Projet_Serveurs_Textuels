	.file	"Connexions_Action.c"
	.text
	.section	.rodata
.LC0:
	.string	"gfre"
	.align 8
.LC1:
	.string	"Liste des commandes disponibles : "
.LC2:
	.string	"\t !login userID MotDePasse "
.LC3:
	.string	"\t !signup pseudo MotDePasse "
.LC4:
	.string	"\t !create servername "
.LC5:
	.string	"\t !join serverID "
.LC6:
	.string	"\t !quit serverID "
.LC7:
	.string	"\t !delete serverID "
.LC8:
	.string	"\t !listserver "
.LC9:
	.string	"\t !listinvitation "
	.align 8
.LC10:
	.string	"\t !accept serverID (invitation) "
.LC11:
	.string	"\t !open serverID "
.LC12:
	.string	"\t !exit "
.LC13:
	.string	"\t !logout"
.LC14:
	.string	"\t !die "
	.text
	.globl	affich_help
	.type	affich_help, @function
affich_help:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	leaq	.LC7(%rip), %rdi
	call	puts@PLT
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
	leaq	.LC10(%rip), %rdi
	call	puts@PLT
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	leaq	.LC12(%rip), %rdi
	call	puts@PLT
	leaq	.LC13(%rip), %rdi
	call	puts@PLT
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	affich_help, .-affich_help
	.section	.rodata
.LC15:
	.string	" "
.LC16:
	.string	"commande incorrecte"
.LC17:
	.string	"r"
.LC18:
	.string	"rsc/utilisateur.dat"
.LC19:
	.string	"utilisateur"
.LC20:
	.string	"Ce pseudo est deja pris !"
	.text
	.globl	signup
	.type	signup, @function
signup:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC15(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -104(%rbp)
	leaq	.LC15(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -96(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L3
	cmpq	$0, -96(%rbp)
	je	.L3
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpq	$30, %rax
	ja	.L3
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpq	$30, %rax
	jbe	.L4
.L3:
	leaq	.LC16(%rip), %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L11
.L4:
	leaq	.LC17(%rip), %rsi
	leaq	.LC18(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -88(%rbp)
	leaq	.LC19(%rip), %rdi
	call	bdd_getSize_table@PLT
	movl	%eax, -108(%rbp)
	movl	$0, -112(%rbp)
	cmpq	$0, -88(%rbp)
	jne	.L7
	movl	$-1, %eax
	jmp	.L11
.L10:
	leaq	-80(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L8
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	leaq	.LC20(%rip), %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L11
.L8:
	addl	$1, -112(%rbp)
.L7:
	movq	-88(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$72, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$-1, %rax
	je	.L9
	movl	-112(%rbp), %eax
	cmpl	-108(%rbp), %eax
	jl	.L10
.L9:
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-96(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	bdd_creer_utilisateur@PLT
	movl	$0, %eax
.L11:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	signup, .-signup
	.section	.rodata
.LC21:
	.string	"Connecte !"
.LC22:
	.string	"Mot de passe incorrecte"
.LC23:
	.string	"utilisateur inexistant"
	.text
	.globl	login
	.type	login, @function
login:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC15(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -104(%rbp)
	leaq	.LC15(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -96(%rbp)
	cmpq	$0, -104(%rbp)
	je	.L14
	cmpq	$0, -96(%rbp)
	je	.L14
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpq	$30, %rax
	ja	.L14
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpq	$30, %rax
	jbe	.L15
.L14:
	leaq	.LC16(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L23
.L15:
	leaq	.LC17(%rip), %rsi
	leaq	.LC18(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -88(%rbp)
	leaq	.LC19(%rip), %rdi
	call	bdd_getSize_table@PLT
	movl	%eax, -108(%rbp)
	movl	$0, -112(%rbp)
	cmpq	$0, -88(%rbp)
	jne	.L18
	movl	$0, %eax
	jmp	.L23
.L22:
	leaq	-80(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L19
	leaq	-80(%rbp), %rax
	leaq	38(%rax), %rdx
	movq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L20
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	leaq	.LC21(%rip), %rdi
	call	puts@PLT
	movq	-80(%rbp), %rax
	jmp	.L23
.L20:
	leaq	.LC22(%rip), %rdi
	call	puts@PLT
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$0, %eax
	jmp	.L23
.L19:
	addl	$1, -112(%rbp)
.L18:
	movq	-88(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$72, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$-1, %rax
	je	.L21
	movl	-112(%rbp), %eax
	cmpl	-108(%rbp), %eax
	jl	.L22
.L21:
	leaq	.LC23(%rip), %rdi
	call	puts@PLT
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$0, %eax
.L23:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L24
	call	__stack_chk_fail@PLT
.L24:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	login, .-login
	.section	.rodata
.LC24:
	.string	"!help"
.LC25:
	.string	"!signup"
.LC26:
	.string	"!login"
.LC27:
	.string	"!exit"
.LC28:
	.string	"Action inexistante"
	.text
	.globl	menuConnexion
	.type	menuConnexion, @function
menuConnexion:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
.L32:
	movq	stdin(%rip), %rdx
	leaq	-144(%rbp), %rax
	movl	$127, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -168(%rbp)
	movl	-168(%rbp), %eax
	subl	$1, %eax
	cltq
	movb	$32, -144(%rbp,%rax)
	movl	-168(%rbp), %eax
	cltq
	movb	$0, -144(%rbp,%rax)
	leaq	-144(%rbp), %rax
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	leaq	.LC24(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L26
	movl	$0, %eax
	call	affich_help
	jmp	.L32
.L26:
	movq	-160(%rbp), %rax
	leaq	.LC25(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L28
	movl	$0, %eax
	call	signup
	jmp	.L32
.L28:
	movq	-160(%rbp), %rax
	leaq	.LC26(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L29
	movl	$0, %eax
	call	login
	movq	%rax, -152(%rbp)
	cmpq	$0, -152(%rbp)
	je	.L32
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	menu_Acceuil@PLT
	movl	%eax, -164(%rbp)
	jmp	.L32
.L29:
	movq	-160(%rbp), %rax
	leaq	.LC27(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L30
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L33
	jmp	.L34
.L30:
	leaq	.LC28(%rip), %rdi
	call	puts@PLT
	jmp	.L32
.L34:
	call	__stack_chk_fail@PLT
.L33:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	menuConnexion, .-menuConnexion
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
