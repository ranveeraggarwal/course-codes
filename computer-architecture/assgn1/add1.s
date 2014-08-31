.text

main:
	li $s0,1
	addi $t0,$s0,2
	li $v0, 1
	move $v0, $t0
	syscall