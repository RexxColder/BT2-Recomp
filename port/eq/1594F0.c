#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void func_00129C38();

void func_001594F0(u8 *arg0) {
    u8 *s0;
    s32 v;
    u16 w;

    s0 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsCharStopped(*(s32 *)*(u8 **)(s0 + 0x8)) != 0) {
        return;
    }
    v = *(s32 *)s0 & ~0x20;
    *(s32 *)s0 = v;
    w = *(u16 *)(arg0 + 0x8);
    if (((w & 4) ? 1 : (w & 1)) != 0) {
        *(s32 *)s0 = v | 0x20;
        func_00129C38(s0 + 0x80, arg0 + 0x10);
        *(s32 *)s0 = (*(s32 *)s0 | 1) & ~0x10;
    }
}
