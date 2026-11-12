#include "common.h"

s32 func_001DCDB8(s32 arg0);

void func_001DC520(u8 *arg0) {
    s32 s0;

    if (*(u8 *)(arg0 + 1) != 3) {
        return;
    }
    s0 = *(s32 *)(arg0 + 0x38);
    if (func_001DCDB8((s32)arg0) == 0) {
        *(u16 *)((u8 *)s0 + 0x24C) = *(u16 *)((u8 *)s0 + 0x24C) | 0x4;
    }
}
