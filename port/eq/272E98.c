#include "common.h"

extern u8 *gBtlStage;

s32 func_00272E98(u8 *arg0) {
    u8 *stage = gBtlStage;
    u8 *v1;
    s32 a2 = 0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;

    if (*(s32 *)(stage + 0x38) == 0) {
        return -1;
    }
    v1 = *(u8 **)(stage + 0x5C) + *(s32 *)(stage + 0x3C) * 4;
    f5 = *(f32 *)(arg0 + 0);
    for (;;) {
        f4 = *(f32 *)(v1 + 0x20) - *(f32 *)(v1 + 0x30);
        f3 = *(f32 *)(v1 + 0x28) - *(f32 *)(v1 + 0x38);
        f1 = *(f32 *)(v1 + 0x20) + *(f32 *)(v1 + 0x30);
        f2 = *(f32 *)(v1 + 0x28) + *(f32 *)(v1 + 0x38);
        v1 += 0x40;
        if (!(f1 < f5 || f2 < *(f32 *)(arg0 + 8) || f5 < f4 || *(f32 *)(arg0 + 8) < f3)) {
            return a2;
        }
        a2++;
        if ((u32)a2 >= (u32)*(s32 *)(stage + 0x38)) {
            return -1;
        }
    }
}
