#include "common.h"

void func_0025FFB8(s32 arg0) {
    s32 p;
    f32 f0;
    f32 f1;
    f32 f2;

    p = arg0 + 0xBD0;
    if (*(s32 *)p == 1) {
        f1 = *(f32 *)(p + 0x10);
        f2 = *(f32 *)(p + 0x08);
        f0 = f1 + *(f32 *)(p + 0x18);
        *(f32 *)(p + 0x14) = f1;
        *(f32 *)(p + 0x10) = f0;
        if (f2 <= f0) {
            *(f32 *)(p + 0x10) = f2;
            *(s32 *)p = 0;
        }
        return;
    }
    if (*(s32 *)p == 2) {
        f0 = *(f32 *)(p + 0x10);
        f1 = f0 + *(f32 *)(p + 0x18);
        *(f32 *)(p + 0x14) = f0;
        *(f32 *)(p + 0x10) = f1;
        if (*(f32 *)(p + 0x08) <= f1) {
            *(f32 *)(p + 0x10) = 0.0f;
        }
        return;
    }
}
