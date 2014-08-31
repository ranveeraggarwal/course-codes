.data
prompt1: .asciiz "Please enter the first number: "
prompt2: .asciiz "Please enter the second number: "
output: .asciiz "Sum of the two numbers is: "
.text
main:
	#Prompt for first input
        li      $v0, 4
        la      $a0, prompt1
        syscall
	#First Input
	li $v0, 5
	syscall
	move $s0, $v0
	#Prompt for second input
        li      $v0, 4
        la      $a0, prompt2
        syscall
	#Second Input
	li $v0, 5
	syscall
	move $s1, $v0
	#Add the numbers
	add $t0, $s0, $s1
	#Prompt for output
        li      $v0, 4
        la      $a0, output
        syscall
	#Print the numbers
	li $v0, 1
	move $a0, $t0
	syscall 
