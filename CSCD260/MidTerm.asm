#Conrad Provan
.data
	sr0: .word 37, 39, 585, 54, 90, 331, 13, 33, 439, 68
	dt1: .space 40
	blankSpace: .asciiz " "
	newLine: .asciiz "\n"
	
.text
main:
	add $t2, $s3, $s7
	add $t2, $t2, $t1
	
	li $t0, 10
	
	la $s0, sr0
	li $t1, 0
	loop1:
		beq $t1, $t0, end1
		lw $a0, ($s0)
		li $v0,1
		syscall
		la $a0, blankSpace
		addi $v0, $0, 4
		syscall
		addi $s0, $s0, 4
		addi $t1, $t1, 1
		j loop1
	end1:
	
	la $a0, newLine
	addi $v0, $0, 4
	syscall
	
	la $s1, dt1
	la $s0, sr0
	li $t1, 0
	li $t2, 6
	addi $sp, $sp, -12
	sw $t2, 8($sp)
	sw $s0, 4($sp)
	sw $s1, 0($sp)
	
	jal copy_array
	
	li $t0, 10
	la $s0, dt1
	li $t1, 0
	loop3:
		beq $t1, $t0, end3
		lw $a0, ($s0)
		li $v0,1
		syscall
		la $a0, blankSpace
		addi $v0, $0, 4
		syscall
		addi $s0, $s0, 4
		addi $t1, $t1, 1
		j loop3
	end3:
	
	addi $sp, $sp, 12
	addi $sp, $sp, -8
	la $s0, sr0
	sw $t2, 4($sp)
	sw $s0, 0($sp)
	
	la $a0, newLine
	addi $v0, $0, 4
	syscall
	
	jal recur_print
	
	li $v0,10
	syscall

copy_array:
	lw $t0, 8($sp)
	lw $s0, 4($sp)
	lw $s1, 0($sp)
	li $t1, 0
	loop2:
		beq $t1, $t0, end2
		lw $t3, ($s0)
		sw $t3, ($s1)
		addi $s0, $s0, 4
		addi $s1, $s1, 4
		addi $t1, $t1, 1
		j loop2
	end2:
jr $ra

recur_print:
	lw $t0, 4($sp)
	lw $s0, 0($sp)
	beq $t0, $0, true
	lw $a0, ($s0)
	li $v0,1
	syscall
	la $a0, blankSpace
	addi $v0, $0, 4
	syscall
	addi $t0, $t0, -1
	addi $s0, $s0, 4
	sw $t0, 4($sp)
	sw $s0, 0($sp)
	jal recur_print
	true:
		jr $ra
jr $ra