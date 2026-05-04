#ifndef BOREALOS_SYSDEPS_HPP
#define BOREALOS_SYSDEPS_HPP

#include <mlibc/sysdep-signatures.hpp>

namespace mlibc {
    struct BorealOSSysdepTags :
    LibcPanic,
    LibcLog,
    Isatty,
    Write,
    TcbSet,
    AnonAllocate,
    AnonFree,
    Seek,
    Exit,
    Close,
    FutexWake,
    FutexWait,
    Read,
    Open,
    VmMap,
    VmUnmap,
    ClockGet
    {};

    template<typename Tag>
    using Sysdeps = SysdepOf<BorealOSSysdepTags, Tag>;
}

#endif //BOREALOS_SYSDEPS_HPP
