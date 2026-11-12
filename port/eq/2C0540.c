#include "common.h"

s32 func_002C0540(void *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];

    ((void (*)(void *, s32, s32, s32 *))(*(void **)((u8 *)*(void **)arg0 + 0x18)))(arg0, arg1, arg2, sp);
    ((void (*)(void *, s32, s32 *))(*(void **)((u8 *)*(void **)arg0 + 0x20)))(arg0, arg1 == 0, sp);
    return sp[1];
}
