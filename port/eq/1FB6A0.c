#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
f32 BtlOpp_GetDistance(s32 arg0);
void BtlOpp_GetTargetPos(s32 arg0, s32 arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
s32 func_003126C8(s32 arg0, s32 arg1);
extern f32 D_00385810;

void func_001FB6A0(s32 arg0, u8 *arg1) {
    s32 sp[16];
    f32 f20;
    f32 f21;
    f32 t;
    f32 k;
    f32 d;

    func_003126C8((s32)&sp[0], arg0 + 0x190);
    f20 = 1.0f;
    func_003126C8((s32)&sp[4], BtlChar_GetPos(arg0));
    BtlOpp_GetTargetPos(arg0, (s32)&sp[8]);
    func_00312650((s32)&sp[12], (s32)&sp[8], (s32)&sp[0]);
    f21 = atan2f(*(f32 *)&sp[12], *(f32 *)&sp[14]);
    d = BtlOpp_GetDistance(arg0);
    if (!(d < 50.0f)) {
        if (d < 1000.0f) {
            f20 = 1.0f - ((d - 50.0f) / D_00385810);
        } else {
            f20 = 0.0f;
        }
    }
    t = (2.0f * f20) - 1.0f;
    k = ((((-t * fabsf(t)) + (2.0f * t)) * 0.5f) + 0.5f) * (1.0f - *(f32 *)(arg0 + 0x150 + 0xA4));
    if (k > 0.0f) {
        *(f32 *)(arg1 + 4) = BtlUtil_WrapAngle(*(f32 *)(arg1 + 4) + (BtlUtil_WrapAngle(f21 - *(f32 *)(arg1 + 4)) * k));
    }
}
