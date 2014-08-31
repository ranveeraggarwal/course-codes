	.file	1 "gcd.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	gcd
	.set	nomips16
	.ent	gcd
	.type	gcd, @function
gcd:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	move	$2,$4  #$2 holds a
	bne	$4,$5,$L7 #a!=b then branch to L7
	j	$31 #return to the value of the branch
$L5:
	bne	$5,$2,$L7 
	j	$31
$L7:
	slt	$3,$5,$2 #$2 = a; if a > b
	beq	$3,$0,$L4 # if b >= a then branch to l4
	subu	$2,$2,$5 #a = a - b
	b	$L5
$L4:
	subu	$5,$5,$2  #a = b - a
	b	$L5 #check if the two values are equal
	.end	gcd
	.size	gcd, .-gcd
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 16, gp= 8
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	addiu	$sp,$sp,-32 
	sw	$31,28($sp)
	.cprestore	16
	li	$4,48			# 0x30 load the immediate value : a0
	li	$5,15			# 0xf load another immendiate value : a1
	jal	gcd
	la	$3,result #store the value of result in register 3 and pull the value stored memory
	sw	$2,0($3)
	move	$4,$2
	jal	syscall_print_int
	jal	syscall_print_newline
	move	$2,$0
	lw	$31,28($sp)
	addiu	$sp,$sp,32
	j	$31
	.end	main
	.size	main, .-main

	.comm	result,4,4
	.ident	"GCC: (GNU) 4.4.7"
