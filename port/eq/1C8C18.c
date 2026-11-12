#include "common.h"

s32 func_001C91F0(s32 arg0);

void func_001C8C18(u8 *arg0) {
    s32 s0;

    if (*(u8 *)(arg0 + 1) != 3) {
        return;
    }
    s0 = *(s32 *)(arg0 + 0x38);
    if (func_001C91F0((s32)arg0) == 0) {
        *(s32 *)((u8 *)s0 + 0x94) = *(s32 *)((u8 *)s0 + 0x94) | 0x4;
    }
}
