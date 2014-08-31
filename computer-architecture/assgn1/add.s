.text

main:
	lui $t0,0x1000
	li $t1,0x0001
	or $t2,$t1,$t0
	lui $t3,0x2000
	li $t4,0x0002
	or $t5,$t3,$t4
	add $t6,$t2,$t5
	li $v0,1
	move $a0,$t6
	syscall