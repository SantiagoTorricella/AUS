.data
	palabra: .word 0x10203040
	octeto: .space 2
		
	
	
.text

	main:
		lw $s0, palabra($0)
		sb $s0, octeto($0)
		
		li $v0,10
		syscall