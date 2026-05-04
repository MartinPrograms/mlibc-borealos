#include <bits/syscall.h>
#include <errno.h>

extern "C" long __do_syscall_ret(unsigned long ret) {
    return ret;
}

using sc_word_t = long;

sc_word_t __do_syscall0(long sc) {
    sc_word_t ret;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc)
         : "memory");
    return ret;
}

sc_word_t __do_syscall1(long sc,
        sc_word_t arg1) {
    sc_word_t ret;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc), "D"(arg1)
         : "memory");
    return ret;
}

sc_word_t __do_syscall2(long sc,
        sc_word_t arg1, sc_word_t arg2) {
    sc_word_t ret;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc), "D"(arg1), "S"(arg2)
         : "memory");
    return ret;
}

sc_word_t __do_syscall3(long sc,
        sc_word_t arg1, sc_word_t arg2, sc_word_t arg3) {
    sc_word_t ret;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc), "D"(arg1), "S"(arg2), "d"(arg3)
         : "memory");
    return ret;
}

sc_word_t __do_syscall4(long sc,
        sc_word_t arg1, sc_word_t arg2, sc_word_t arg3,
        sc_word_t arg4) {
    sc_word_t ret;
    register sc_word_t r10 asm("r10") = arg4;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10)
         : "memory");

    return ret;
}

sc_word_t __do_syscall5(long sc,
        sc_word_t arg1, sc_word_t arg2, sc_word_t arg3,
        sc_word_t arg4, sc_word_t arg5) {
    sc_word_t ret;
    register sc_word_t r10 asm("r10") = arg4;
    register sc_word_t r8 asm("r8") = arg5;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8)
         : "memory");
    return ret;
}

sc_word_t __do_syscall6(long sc,
        sc_word_t arg1, sc_word_t arg2, sc_word_t arg3,
        sc_word_t arg4, sc_word_t arg5, sc_word_t arg6) {
    sc_word_t ret;
    register sc_word_t r10 asm("r10") = arg4;
    register sc_word_t r8 asm("r8") = arg5;
    register sc_word_t r9 asm("r9") = arg6;
    asm ("syscall"
         : "=a"(ret)
         : "a"(sc), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8), "r"(r9)
         : "memory");

    return ret;
}
