.data
	list: .space 40
	newLine: .asciiz "\n"
.text
.globl main
main:
	la $s0, list
	li $t0, 10
	li $t1, 0
	loop1:
		beq $t1, $t0, end1
		li $v0, 5
		syscall
		addi $sp, $sp, -8
		sw $v0, 4($sp)
		sw $s0, 0($sp)
		jal store1
		addi $sp, $sp, 8
		addi $s0, $s0, 4
        addi $t1, $t1, 1
		j loop1
	end1:
	la $a0, newLine
	addi $v0, $0, 4
	syscall
	la $s0, list
	li $t1, 0
	loop2:
		beq $t1, $t0, end2
		lw $a0, ($s0)
		li $v0,1
		syscall
		la $a0, newLine
		addi $v0, $0, 4
		syscall
		addi $s0, $s0, 4
		addi $t1, $t1, 1
		j loop2
	end2:
li $v0,10
syscall

store1:
	lw $t2, 4($sp)
	lw $t3, 0($sp)
	sw $t2, 0($t3)
jr $ra