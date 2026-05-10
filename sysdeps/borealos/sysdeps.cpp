#include "mlibc/tcb.hpp"
#include <abi-bits/errno.h>
#include <bits/ensure.h>
#include <bits/syscall.h>
#include <mlibc/all-sysdeps.hpp>
#include <string.h>
#include "SyscallList.h"

#undef __STRINGIFY
#define __STRINGIFY(x) #x

#define STUB() ({ \
    sysdep<LibcLog>("Stub: " __FILE__ ":" __STRINGIFY(__LINE__)); \
    __builtin_unreachable(); \
})

#define ARCH_SET_FS 0x1002
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_ANONYMOUS 0x20
#define MAP_PRIVATE 0x02

namespace mlibc {
    void Sysdeps<LibcPanic>::operator()() {
        Sysdeps<LibcLog>()("Panic called");
        __builtin_unreachable();
    }

    void Sysdeps<LibcLog>::operator()(const char *msg) {
        Sysdeps<Write>()(2, msg, strlen(msg), nullptr);
    }

    int Sysdeps<Isatty>::operator()(int fd) {
        return 0;
    }

    int Sysdeps<Write>::operator()(int fd, void const *buf, size_t size, ssize_t *ret) {
        if (size == 0) {
            if (ret)
                *ret = 0;
            return 0;
        }

        ssize_t result = __do_syscall3((uint64_t)Syscalls::ID::WRITE, fd, (uintptr_t)buf, size);
        if (result < 0) {
            return -1;
        }

        if (ret)
            *ret = result;
        return 0;
    }

    int Sysdeps<TcbSet>::operator()(void *pointer) {
        // ARCH_SET_FS = 0x1002
        if (__do_syscall2((uint64_t)Syscalls::ID::ARCH_PRCTL, 0x1002, (uintptr_t)pointer) != 0) {
            return -1;
        }
        return 0;
    }

    int Sysdeps<AnonAllocate>::operator()(size_t size, void **pointer) {
        void *result = (void *)__do_syscall6((uint64_t)Syscalls::ID::MMAP, 0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if ((uintptr_t)result > (uintptr_t)-4096) {
            return -1;
        }

        *pointer = result;
        return 0;
    }

    int Sysdeps<AnonFree>::operator()(void *pointer, size_t size) {
        if (__do_syscall2((uint64_t)Syscalls::ID::MUNMAP, (uintptr_t)pointer, size) != 0) {
            return -1;
        }
        return 0;
    }

    int Sysdeps<Seek>::operator()(int, off_t, int, off_t *) {
        return 0;
    }

    void Sysdeps<Exit>::operator()(int status) {
        __do_syscall1((uint64_t)Syscalls::ID::EXIT, status);
        __builtin_unreachable();
    }

    int Sysdeps<Close>::operator()(int) {
        return 0;
    }

    int Sysdeps<FutexWake>::operator()(int *, bool) {
        return 0;
    }

    int Sysdeps<FutexWait>::operator()(int *, int, timespec const *) {
        return 0;
    }

    int Sysdeps<Read>::operator()(int fd, void * buf, size_t count, ssize_t *ret) {
        ssize_t result = __do_syscall3((uint64_t)Syscalls::ID::READ, fd, (uintptr_t)buf, count);
        if (result < 0) {
            return -1;
        }

        if (ret)
            *ret = result;
        return 0;
    }

    int Sysdeps<Open>::operator()(const char *, int, unsigned int, int *) {
        return 0;
    }

    int Sysdeps<VmMap>::operator()(void *addr, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
        void *result = (void *)__do_syscall6((uint64_t)Syscalls::ID::MMAP, (uintptr_t)addr, size, prot, flags, fd, offset);
        if ((uintptr_t)result > (uintptr_t)-4096ULL)
            return ENOMEM;
        *window = result;
        return 0;
    }

    int Sysdeps<VmUnmap>::operator()(void *pointer, size_t size) {
        if (__do_syscall2((uint64_t)Syscalls::ID::MUNMAP, (uintptr_t)pointer, size) != 0) {
            return -1;
        }
        return 0;
    }

    int Sysdeps<ClockGet>::operator()(int, time_t *, long *) {
        return 0;
    }

    void Sysdeps<Yield>::operator()() {
        __do_syscall0((uint64_t)Syscalls::ID::YIELD);
    }
}