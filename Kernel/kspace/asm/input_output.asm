GLOBAL _read_byte
GLOBAL _read_word
GLOBAL _write_byte
GLOBAL _write_word

section .text

; _read_byte(word address) :
;   returns a byte from the I/OM at the given address.
;   dx: address.
_read_byte:
	push rbp
	mov rbp, rsp

    mov rdx, rdi
    in al, dx

    mov rsp, rbp
    pop rbp
    ret

; _read_word(word address) :
;   returns 2 bytes from the I/OM at the given address.
;   dx: address.
_read_word:
	push rbp
	mov rbp, rsp

    mov rdx, rdi
    in ax, dx

    mov rsp,rbp
    pop rbp
    ret

; _write_byte(word address, byte data):
;   writes a byte in the I/OM at the given address.
;   dx: address.
;   al: byte of data.
_write_byte:
    push rbp
    mov rbp, rsp

    mov rdx, rdi
    mov rax, rsi
    out dx, al


; _write_word(word address, word data):
;   writes 2 bytes in the I/OM at the given address.
;   dx: address.
;   al: word of data.
_write_word:
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	mov rax, rsi
	out dx, ax

	mov rsp, rbp
	pop rbp
	ret