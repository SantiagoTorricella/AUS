.data 
numero1: .word 0x8FB53A4B
numero2: .space 4
		 .text
		 
main:
	lw $t1, numero1($0)
	sll $t0, $t1, 5
	sw $t0, numero2($0)