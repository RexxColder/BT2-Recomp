#include "common.h"

extern f32 D_00384CA0;

void func_00196B28(u8 *arg0) {
    u8 *p = arg0 + 0xA10;
    s32 v = *(s32 *)(p + 0xB0);

    if (v != 0 && !(v & 0x10)) {
        *(s32 *)(p + 0xB0) = v | 0x10;
        *(f32 *)(p + 0x94) = *(f32 *)(p + 0x90) / D_00384CA0;
    }
}
