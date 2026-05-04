#include "mlibc/tcb.hpp"
#include <abi-bits/errno.h>
#include <bits/ensure.h>
#include <bits/syscall.h>
#include <mlibc/all-sysdeps.hpp>
#include <string.h>

#undef __STRINGIFY
#define __STRINGIFY(x) #x

#define STUB() ({ \
    sysdep<LibcLog>("Stub: " __FILE__ ":" __STRINGIFY(__LINE__)); \
    __builtin_unreachable(); \
})

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_EXIT 60
#define SYS_MMAP 9
#define SYS_ARCH_PRCTL 158
#define ARCH_SET_FS 0x1002

namespace mlibc {
    void Sysdeps<LibcPanic>::operator()() {

    }

    void Sysdeps<LibcLog>::operator()(const char *msg) {
    }

    int Sysdeps<Isatty>::operator()(int fd) {
    }

    int Sysdeps<Write>::operator()(int fd, void const *buf, size_t size, ssize_t *ret) {
    }

    int Sysdeps<TcbSet>::operator()(void *pointer) {
    }

    int Sysdeps<AnonAllocate>::operator()(size_t size, void **pointer) {
    }

    int Sysdeps<AnonFree>::operator()(void *, unsigned long) {
    }

    int Sysdeps<Seek>::operator()(int, off_t, int, off_t *) {
    }

    void Sysdeps<Exit>::operator()(int status) {
    }

    int Sysdeps<Close>::operator()(int) {
    }

    int Sysdeps<FutexWake>::operator()(int *, bool) {
    }

    int Sysdeps<FutexWait>::operator()(int *, int, timespec const *) {
    }

    int Sysdeps<Read>::operator()(int fd, void * buf, size_t count, ssize_t *ret) {
    }

    int Sysdeps<Open>::operator()(const char *, int, unsigned int, int *) {
    }

    int Sysdeps<VmMap>::operator()(void *, size_t, int, int, int, off_t, void **) {
    }

    int Sysdeps<VmUnmap>::operator()(void *, size_t) {
    }

    int Sysdeps<ClockGet>::operator()(int, time_t *, long *) {
    }
}