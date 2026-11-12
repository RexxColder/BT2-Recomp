#include "common.h"

extern s32 Syscall_0x23();

/* 0x00100250: syscall stub (BT3 _root): v1 = 0x23, then syscall. */
s32 _root(s32 a0, s32 a1, s32 a2, s32 a3) {
    return Syscall_0x23(a0, a1, a2, a3);
}
