#include "common.h"

u8 *BtlChar_GetPos(s32 arg0, s32 arg1);
extern f32 D_00385AD0;

void func_00216800(f32 farg0, s32 arg1, s32 arg2) {
    u8 *s0;

    s0 = BtlChar_GetPos(arg1, arg2);
    *(f32 *)(s0 + 0xC4) = *(f32 *)(s0 + 0xC4) + D_00385AD0;
    if (farg0 < *(f32 *)(BtlChar_GetPos(arg1, arg2) + 0xC4)) {
        *(f32 *)(BtlChar_GetPos(arg1, arg2) + 0xC4) = farg0;
    }
    s0 = BtlChar_GetPos(arg1, arg2);
    *(f32 *)(s0 + 0x4) = *(f32 *)(s0 + 0x4) + *(f32 *)(BtlChar_GetPos(arg1, arg2) + 0xC4);
}
