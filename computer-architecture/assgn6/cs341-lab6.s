;;Questions
;Branch prediction technique: Always, branch not taken. If taken, then stop the execution and go to the branch
;Branch requires inputs in the second stage as in the first stage Instruction Fetching happens.

.data
A:    .word 10
B:    .word 8
C:    .word 0

.text
main:
;Creating a data stall
lw r2, 0(r1)
beq r2, r0, branch

;Control stall
daddi r3, r0, 1
daddi r6, r0, 1
beq r3, r6, branch
daddi r4, r0, 1
branch:

;A stall before ID
daddi r5, r0, 2
beq r5, r6, anotherbranch
anotherbranch:

;Data forwarding from EX to ID
dadd r6, r6, r3
beq r6, r3, yetanotherbranch
yetanotherbranch:

;Data forwarding from MEM to ID
lwu r1, A(r0)
lw r2, 0(r1)
beq r1, r2, branchnext
branchnext:

;Longest possible stall
dmul r8, r7, r6
dmul r5, r6, r8

;Max distance for forwarding k->k+2
lw r2, 0(r1)
daddi r3, r3, 1
daddi r4, r4, 1
beq r2, r3, andanotherbranch
andanotherbranch:

;WAW
dmul r2,r3,r4
daddi r2, r4, 3

;Structural Stall
dmul r8, r6, r7
daddi r3, r3, 1
halt 
