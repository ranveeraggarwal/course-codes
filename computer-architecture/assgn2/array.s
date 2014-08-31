.data
prompt: .asciiz "Enter the number: "
.align 2
list: 	.space 32

.text
main:	
	li $s0, 8
	la $s1, list
	li $t0, 0
loop:
	beq $t0, $s0, exit
	#Prompt
	li $v0, 4
        la $a0, prompt
        syscall
	#Input
	li $v0, 5
	syscall
	#Loop
	move $t1, $v0
	sw $t1, 0($s1) 
	addi $s1, $s1, 4 # step to next array cell
	addi $t0, $t0, 1 # count increment
	j loop
exit:
	li $v0, 10
	syscall