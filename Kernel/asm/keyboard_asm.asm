GLOBAL read_key

SECTION .text

read_key:
	in al, 60h
	movzx rax, al
	ret
