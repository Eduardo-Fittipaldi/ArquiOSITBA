GLOBAL _callerino

SECTION .text

_callerino:
    push rbp
    mov rbp, rsp

    int 80h

    mov rsp, rbp
    pop rbp
    ret
