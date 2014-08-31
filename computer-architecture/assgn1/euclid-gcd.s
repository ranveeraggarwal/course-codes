.text

main:
	lui $t7,0x0000
	li $t6,0x0003
	or $s0,$t6,$t7
	lui $t5,0x0000
	li $t4,0x0006
	or $s1,$t5,$t4

	ori $s2,$0,0

	LOOP:
		beq $s1,$0,EXIT1
		slt $t0,$s0,$s1
		beq $t0,$0,EXIT2
			addi $s2,$s0,0
			addi $s0,$s1,0
			addi $s1,$s2,0
		EXIT2:
		addi $s2,$s1,0
		sub $s1,$s0,$s1
		addi $s0,$s2,0
		j LOOP	
	EXIT1:

	li $v0,1
	move $a0,$s0
	syscall
	
