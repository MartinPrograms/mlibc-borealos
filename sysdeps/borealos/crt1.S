.section .data
.global __dso_handle
.hidden __dso_handle
__dso_handle:
    .quad 0

.section .text
.global _start
.type _start, @function

_start:
    xorq %rbp, %rbp
    popq %rsi
    movq %rsp, %rdx
    andq $-16, %rsp
    leaq 8(%rdx,%rsi,8), %rcx
    leaq main(%rip), %rdi
    call _mlibc_entry
.Lhalt:
    hlt
    jmp .Lhalt