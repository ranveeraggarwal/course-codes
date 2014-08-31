FACT:
	addi $sp, $sp, -8
	sw $a0, 0($sp)
	sw $ra, 4($sp)
	bne $a0, $0, ELSE
	ori $v0, $0, 1
	j END
ELSE:
	addi $a0, $a0, -1
	jal FACT
	lw $a0, 0($sp)
	mul $v0, $v0, $a0

END:
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	jr $ra
main:
	ori $a0, $0, 5
	jal FACT
        move $a0, $v0
	li $v0, 1
        syscall
