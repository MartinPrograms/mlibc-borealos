.section .text
.global _start
.type _start, @function

_start:
    xorq %rbp, %rbp
    movq %rsp, %rdi
    andq $-16, %rsp
    movq $main, %rsi
    call __mlibc_entry
.section .note.GNU-stack,"",%progbits
