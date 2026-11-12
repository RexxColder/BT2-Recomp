#include "common.h"

s32 func_001CD860(s32 arg0);

void func_001CD1D0(u8 *arg0) {
    s32 s0;

    if (*(u8 *)(arg0 + 1) != 2) {
        return;
    }
    s0 = *(s32 *)(arg0 + 0x38);
    if (func_001CD860((s32)arg0) == 0) {
        *(u16 *)((u8 *)s0 + 0x12C) = *(u16 *)((u8 *)s0 + 0x12C) | 0x4;
    }
}
