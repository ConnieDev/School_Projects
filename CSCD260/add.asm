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
	# prompt user to enter  
	li $v0, 4
	la $a0, prompt
	syscall
	# get user input
	li $v0, 5
	syscall
	# move input
	move $t1, $v0
	# add user inputs
	add $t2, $t1, $t0
	# print Message
	li $v0, 4
	la $a0, message
	syscall
	# print sum
	li $v0,1
	move $a0, $t2
	syscall
jr $ra