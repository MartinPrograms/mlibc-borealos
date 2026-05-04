#include <stddef.h>

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

extern "C" {

    extern void (*__init_array_start[])(void);
    extern void (*__init_array_end[])(void);
    extern void (*__fini_array_start[])(void);
    extern void (*__fini_array_end[])(void);

    static void run_init_array() {
        size_t n = (size_t)(__init_array_end - __init_array_start);
        for (size_t i = 0; i < n; i++)
            __init_array_start[i]();
    }

    static void run_fini_array() {
        size_t n = (size_t)(__fini_array_end - __fini_array_start);
        // reverse order per C++ spec
        for (size_t i = n; i > 0; i--)
            __fini_array_start[i - 1]();
    }

    void _mlibc_entry( int (*main)(int, char **, char **), int argc, char **argv, char **envp) {
        environ = envp;
        run_init_array();
        int ret = main(argc, argv, envp);
        run_fini_array();
        exit(ret);
    }
}
