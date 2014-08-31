.data
prompt: .asciiz "Enter a number:"
newline: .asciiz "\n"

.align 2
arr:	.space 32
.align 2
res:	.space 32

.text
#MERGE FUNCTION
merge: 	#store address of array 1 in $a0, size of array 1 in $a1, address of array 2 in $a2, size of array 2 in $a3.
	#lw $ra, 0($sp)
	lw $t0, 0($sp)
	lw $v0, 0($sp)
	
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

#MERGE-SORT
mergesort:
	#storing starting address in a0, length of array in a1
	addi $sp, $sp, -12		#increment stack pointer by 12
	sw $a0, 0($sp) 			#storing the first argument
	sw $a1, 4($sp) 			#storing the second argument
	sw $ra, 8($sp) 			#storing ra	
	li $t0, 1      			#this is required for testing whether the array size is 1
	bne $a1, $t0, mergeelse 	#if the size of the array is 1, go in here
	lw $v0, 0($a0)			#if the size is 1, store the argument's 1st value in return value
	j mergeexit			#jump to exit

mergeelse:
	ori $t0, $a0, 0			#set $t0 to $a0
	srl $t1, $a1, 1			#set $t1 to $a1/2
	sll $t3, $t1, 2			#set $t3 to 4*$t1; this in turn will facilitate the movement of memory pointer
	add $t2, $a0, $t3		#set $t2 to 4*t1 + address of initial pointer of $a0
	ori $t3, $t1, 0			#set $t3 to a value, same as $t1 -- this will contain half of $a1
	addi $sp, $sp, -16		#increment stack pointer by 16
	sw $t0, 0($sp)			#store t0
	sw $t1, 4($sp)			#store t1
	sw $t2, 8($sp)			#store t2
	sw $t3, 12($sp)			#store t3

	#merge 1
	lw $a0, 0($sp)			#initilise a0, first half of the array
	lw $a1, 4($sp)			#initilise a1, first half of the array
	jal mergesort			#call mergesort on first half
	
	#merge 2
	lw $a0, 8($sp)			#initilise a0, second half of the array
	lw $a1, 12($sp)			#initilise a1, second half of the array
	jal mergesort			#call mergesort on second half

	#merge the two
	lw $a0, 0($sp)
	lw $a1, 4($sp)
	lw $a2, 8($sp)
	lw $a3, 12($sp)
	la $t5, res
	addi $sp, $sp, -4
	sw $t5, 0($sp)
	jal merge
	addi $sp, $sp, 20
	lw $a0, 0($sp)
	lw $a1, 4($sp)

	li $t6, 0
	la $t5, res
copyloop:
	beq $t6, $a1, out
	sll $t7, $t6, 2
	add $s0, $a0, $t7
	add $s1, $t5, $t7
	lw $t8, 0($s1)
	sw $t8, 0($s0)
	addi $t6, $t6, 1
	j copyloop
out:
mergeexit:
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra

#MAIN LOOP
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
		la $a0, arr
		li $a1, 8
		jal mergesort
		ori $s2, $a0, 0
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
