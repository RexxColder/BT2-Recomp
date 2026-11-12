#include "common.h"

s32 func_002C0690(void *a0, s32 a1);
void *memcpy(void *arg0, const void *arg1, u32 arg2);

void func_002C6DA8(void *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s2;

    s1 = (u8 *)arg0;
    s2 = s1 + 0xDC4;
    s0 = s1 + 0x1FB8;
    if (*(s32 *)(s0 + 0x20) < 0) {
        s32 v0 = func_002C0690(arg0, *(s32 *)(s0 + 0x10));
        *(s32 *)(s0 + 0x20) = v0 + 4;
    }
    if (*(s32 *)(s2 + 0x24) < 0) {
        memcpy(s2, s1 + 0xD98, 0x2C);
    }
}
