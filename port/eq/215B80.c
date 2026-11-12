#include "common.h"

void *BtlChar_GetPos(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
f32 BtlUtil_WrapAngle(f32 farg0);
extern f32 D_00385A90;
extern f32 D_00385A94;
extern f32 D_00385A98;

void func_00215B80(u8 *arg0, f32 farg0, f32 farg1, f32 farg2) {
    u8 *pos;
    f32 deadzone;
    f32 d;
    f32 var;
    f32 t;

    pos = (u8 *)BtlChar_GetPos((s32)arg0, farg0, farg1, farg2);
    deadzone = D_00385A94;

    *(f32 *)(pos + 0xB0) = *(f32 *)(pos + 0xB0) + farg1 * -*(f32 *)(arg0 + 0xC);
    *(f32 *)(pos + 0xB4) = *(f32 *)(pos + 0xB4) + farg0 * *(f32 *)(arg0 + 0x8);
    if (*(f32 *)(pos + 0xB0) < D_00385A90) {
        *(f32 *)(pos + 0xB0) = D_00385A90;
    }
    if (D_00385A98 < *(f32 *)(pos + 0xB0)) {
        *(f32 *)(pos + 0xB0) = D_00385A98;
    }

    t = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4));
    *(f32 *)(pos + 0xB4) = t;
    d = BtlUtil_WrapAngle(t - *(f32 *)(pos + 0x14));
    var = (d < 0.0f ? -d : d) * farg2;
    if (var < deadzone) {
        var = deadzone;
    }

    if (d < -var) {
        *(f32 *)(pos + 0x14) = BtlUtil_WrapAngle(*(f32 *)(pos + 0x14) - var);
    } else if (var < d) {
        *(f32 *)(pos + 0x14) = BtlUtil_WrapAngle(*(f32 *)(pos + 0x14) + var);
    } else {
        *(f32 *)(pos + 0x14) = *(f32 *)(pos + 0xB4);
    }
}
