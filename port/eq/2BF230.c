#include "common.h"

u8 *func_002BF2C0(s32 arg0);
void func_002ED4D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002F6790(s32 arg0, s32 arg1);
extern u8 func_002BE288[] __attribute__((section(".data")));

u8 *func_002BF230(u8 *arg0) {
    u8 *a2;
    u8 *s0;
    s32 s1;
    u8 *v0;

    v0 = func_002BF2C0((s32)arg0);
    a2 = v0;
    if (a2 != NULL) {
        s0 = *(u8 **)(arg0 + 0x2004);
        v0 = NULL;
        s1 = *(s32 *)(s0 + 0);
        if (*(s32 *)(s0 + 0x34) == 0 && *(s32 *)(a2 + 0) != 0) {
            func_002ED4D8(s1, *(s32 *)(a2 + 0xC), *(s32 *)(a2 + 0x10), *(s32 *)(a2 + 0x14));
            func_002F6790(s1, 0);
            *(s32 *)(s0 + 0x34) = 1;
            v0 = NULL;
            *(s32 *)(s0 + 0x3C) = (s32)func_002BE288;
        }
    }
    return v0;
}
