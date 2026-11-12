#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0025FED8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p = arg0 + 0xBD0;
    u8 *q;
    f32 f1;
    f32 g;

    if ((u8)arg4 == 1) {
        if (arg1 >= 8 || arg1 < 0) {
            return;
        }
        q = *(u8 **)(arg0 + arg1 * 4 + 0x724);
    } else {
        q = *(u8 **)(arg0 + arg1 * 4 + 0x60);
    }
    *(u8 **)(p + 0x28) = q;
    if (q == NULL) {
        return;
    }
    *(u16 *)(p + 4) = (u16)arg1;
    f1 = (f32)*(u16 *)(q + 2);
    *(f32 *)(p + 8) = f1;
    if ((u8)arg3 != 0) {
        *(s32 *)(p + 0x10) = 0;
        *(s32 *)(p + 0x14) = 0;
    } else {
        if (f1 < *(f32 *)(p + 0x10)) {
            *(f32 *)(p + 0x10) = f1;
        }
        g = *(f32 *)(p + 8);
        if (g < *(f32 *)(p + 0x14)) {
            *(f32 *)(p + 0x14) = g;
        }
    }
    memset(p + 0x30, 0, 0x8E);
    *(s32 *)(p + 0) = arg2;
}
