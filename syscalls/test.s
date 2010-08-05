	.file	"test.c"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$1, -4(%ebp)
	movl	$1, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	leal	(%edx,%eax), %eax
	movl	%eax, -12(%ebp)
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
