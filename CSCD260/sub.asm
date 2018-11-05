.data
	prompt: .asciiz "Enter your a number: "
	message: .asciiz "\nYour Sum is: "
.text
.globl main
main:
	
	# prompt user to enter  
	li $v0, 4
	la $a0, prompt
	syscall
	
	# get user input
	li $v0, 5
	syscall
	
	# move input 
	move $t0, $v0
	addi $sp, $sp, -8
	sw $t0, 0($sp)
	
	# prompt user to enter  
	li $v0, 4
	la $a0, prompt
	syscall
	
	# get user input
	li $v0, 5
	syscall
	
	# move input
	move $t1, $v0
	sw $t1, 4($sp)
	jal subtrac

	li $v0,10
	syscall


subtrac:
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	sub $t3,$t0,$t1
	move $a0,$t3
	li $v0,1
	syscall
jr $ra