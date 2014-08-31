.data
newline: .asciiz	"\n"
.align 2
result: .space 4

.text

syscall_print_int:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	li	$v0, 1
	# Using $a0 as argument
	syscall
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr	$ra
	nop

syscall_print_newline:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	li	$v0, 4
	la	$a0, newline
	syscall
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	nop


	.file	1 "gcd.c"
	.text
	.align	2
	.globl	gcd
	.set	nomips16
	.ent	gcd
gcd:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	reorder
	addiu	$sp,$sp,-8		#decrement the stack pointer to store argumetns and $ra
	sw	$fp,4($sp)			#fp points to the first element of this frame
	move	$fp,$sp			#store the value of $sp into $fp
	sw	$4,8($fp)			#store $a0 into 8+fp
	sw	$5,12($fp)			#store $a1 into 12 +fp
$L5:
	lw	$3,8($fp) 
	lw	$2,12($fp)
	#nop
	bne	$3,$2,$L2			#$2 = $a0 = b if(a!=b) goto L2 else return a
	lw	$2,8($fp)			#$3 = $a1 = a
	move	$sp,$fp  
	lw	$fp,4($sp)    
	addiu	$sp,$sp,8
	j	$31
$L2:
	lw	$3,8($fp)
	lw	$2,12($fp)
	#nop					#a=$3, b=$2
	slt	$2,$2,$3			#if a > b
	beq	$2,$0,$L3			#if a <= b goto L3
	lw	$3,8($fp) 
	lw	$2,12($fp)
	#nop
	subu	$2,$3,$2		#$2 = a - b
	sw	$2,8($fp)			#store new a = a - b
	b	$L5					#recurse back
$L3:						#when b >= a
	lw	$3,12($fp)
	lw	$2,8($fp)
	#nop
	subu	$2,$3,$2		#b = b - a
	sw	$2,12($fp)			#recurse
	b	$L5
	.end	gcd

	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$fp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	reorder
	addiu	$sp,$sp,-40
	sw	$31,36($sp)			#$31 = $ra
	sw	$fp,32($sp)
	move	$fp,$sp			#$fp stores the value of $sp	
	sw	$4,40($fp)			#os arguments to be stored
	sw	$5,44($fp)			#store the values of system call
	li	$2,48			# 0x30
	sw	$2,28($fp)			#28($fp) stores 48
	li	$2,15			# 0xf
	sw	$2,24($fp)			#24($fp) stores 15
	lw	$4,28($fp)			#$4=a0 contains 48
	lw	$5,24($fp)			#$5=a1 contains 15
	jal	gcd					#call to gcd function
	move	$3,$2			#move $v0 into $3 
	la	$2,result			#load result from $2
	sw	$3,0($2)			#store the returned value in memory
	la	$2,result 
	lw	$2,0($2)
	#nop
	move	$4,$2			#store the value of result in $4
	jal	syscall_print_int	#print this value
	jal	syscall_print_newline #print newline
	move	$2,$0
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	.end	main
