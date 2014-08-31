.data
prompt: .asciiz "Enter a number:"
newline: .asciiz "\n"

.align 2
arr:	.space 32
.align 2
res:	.space 32

.text
merge: 	#store address of array 1 in $a0, size of array 1 in $a1, address of array 2 in $a2, size of array 2 in $a3.
	#lw $ra, 0($sp)
	lw $t0, 0($sp)
	lw $v0, 0($sp)
	addi $sp, $sp, 4
	
	li $t1, 0 #i
	li $t2, 0 #j
	li $t3, 0 #loop pointer
	add $t4, $a1, $a3 #loop goes till here
	#lw $t6, 0($a0)
	forloop:
		slt $t5, $t3, $t4
		beq $t5, $0, endloop
		slt $t5, $t1, $a1
		beq $t5, $0, addarrtwo
		slt $t5, $t2, $a3
		beq $t5, $0, addarrone
		#actual else begins
		lw $t6, 0($a0) #arr1[i]
		lw $t7, 0($a2) #arr2[j]
		slt $t8, $t6, $t7 
		beq $t8, $0, actif #if arr1[j]>arr2[i], go to actif
		sw $t6, 0($t0) #else appended arr1[i] to res
		j updateone #update the usual incrementors and memo locations
		actif:
			sw $t7, 0($t0) #appended arr2[j] to res
			j updatetwo #update the usual incrementors and memo locations
		addarrtwo:
			lw $t7, 0($a2) #arr2[j]
			sw $t7, 0($t0) #appended arr2[j] to res
			j updatetwo
		addarrone:
			lw $t6, 0($a0) #arr1[i]
			sw $t6, 0($t0) #appended arr2[j] to res
			j updateone
		updateone:
			addi $t0, $t0, 4 #incremented memory loc of result
			addi $t3, $t3, 1 #incremented loop pointer
			addi $a0, $a0, 4 #incremented memory loc of arr1
			addi $t1, $t1, 1 #incremented i
			j forloop #jump back to the for loop		
		updatetwo:
			addi $t0, $t0, 4 #incremented memory loc of result
			addi $t3, $t3, 1 #incremented loop pointer
			addi $a2, $a2, 4 #incremented memory loc of arr2
			addi $t2, $t2, 1 #incremented j
			j forloop #jump back to the for loop
	endloop:
		jr $ra
	
main:
	li $s0, 8
	la $s1, arr #s1 contains the input array
	la $s2, res #s2 contains the output array
	li $t0, 0
	loop: #for inputting numbers
		beq $t0, $s0, exitloop
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
	exitloop: #8 numbers have been now taken in
		#arguments to merge
		la $a0, arr
		li $a1, 4
		addi $a2, $a0, 16
		li $a3, 4
		addi $sp, $sp, -4
		sw $s2, 0($sp)
		jal merge
		la $s2, res
		li $t0, 1
		li $t1, 9
print:
	slt $t2, $t0, $t1
	beq $t2, $0, end_print
	
	li $v0, 1
	lw $a0, 0($s2)
	syscall

	li $v0, 4
	la $a0, newline
	syscall
	
	addi $t0, $t0, 1
	addi $s2, $s2, 4

	j print

end_print:
