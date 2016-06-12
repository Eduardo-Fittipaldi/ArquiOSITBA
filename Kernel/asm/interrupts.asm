;
; interrups.asm
;
; Created on: Apr 18, 2010
;      Author: anizzomc
;

GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL int_08_hand
GLOBAL _lidt
GLOBAL haltcpu

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler


EXTERN irqDispatcher
EXTERN int_08

;RowDaBoat - Wyrm - Kernel/CPU/irqHandlers.asm
%macro	pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push fs
	push gs
%endmacro

;RowDaBoat - Wyrm - Kernel/CPU/irqHandlers.asm
%macro	popState 0
	pop gs
	pop fs
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1

	pushState

	mov rdi, %1	;Paso el parametro por rdi para llamar a irqDispatcher

	call irqDispatcher
	
	;signal pic
	mov al, 20h
	out 20h, al

	popState

	iretq		;iret de 64
%endmacro



SECTION .text

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
    push rbp
    mov rbp, rsp
    mov rax, rdi		; Pasa por registro
    out	21h,al
    pop rbp
    ret

picSlaveMask:
    push    rbp
    mov     rbp, rsp
    mov     rax, rdi  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    ret

_lidt:				; Carga el IDTR
    push    rbp
    mov     rbp, rsp
    push    rbx
    mov     rbx, [rbp + 6] ; ds:bx = puntero a IDTR. ESTO FUNCIONA ASI?
    rol	    rbx,16
    lidt    [rbx]          ; carga IDTR
    pop     rbx
    pop     rbp
    ret


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0
	
;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3
	
;Serial Port 1 and 3	
_irq04Handler:
	irqHandlerMaster 4
	
;USB
_irq05Handler:
	irqHandlerMaster 5


int_08_hand:				; Handler de INT 8 ( Timer tick)
    push    ds
    push    es                      ; Se salvan los registros
    pusha                           ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax
    mov     es, ax
    call    int_08
    mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa
    pop     es
    pop     ds
    iret

haltcpu:
	cli
	hlt
	ret

