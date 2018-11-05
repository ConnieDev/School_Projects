.data

.text

main:
	li $v0, 5
	syscall

	beq $v0, 0, True
	li $t1, 1
	b fin
	True:
		li $t1, 0
	fin:
		li $v0,1
		move $a0, $t1
		syscall
	