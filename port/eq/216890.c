#include "common.h"

void *BtlChar_GetPos(void *arg0);

/* 0x00216890: move the fighter's pose Y (+0xC4) toward arg2 by arg1 (clamped), then pose +0x4 += pose +0xC4. */
void func_00216890(void *arg0, f32 arg1, f32 arg2) {
    u8 *p;

    p = BtlChar_GetPos(arg0);
    if (arg1 < *(f32 *)(p + 0xC4) - arg2) {
        p = BtlChar_GetPos(arg0);
        *(f32 *)(p + 0xC4) = *(f32 *)(p + 0xC4) - arg2;
    } else {
        p = BtlChar_GetPos(arg0);
        if (*(f32 *)(p + 0xC4) + arg2 < arg1) {
            p = BtlChar_GetPos(arg0);
            *(f32 *)(p + 0xC4) = *(f32 *)(p + 0xC4) + arg2;
        } else {
            p = BtlChar_GetPos(arg0);
            *(f32 *)(p + 0xC4) = arg1;
        }
    }
    BtlChar_GetPos(arg0);
    p = BtlChar_GetPos(arg0);
    *(f32 *)(p + 0x4) = *(f32 *)(p + 0x4) + *(f32 *)(p + 0xC4);
}
