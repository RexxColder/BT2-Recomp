#include "common.h"

u8 *BtlChar_GetPos(s32 arg0, u8 *arg1, f32 farg0, f32 farg1);
void func_00312650(f32 *a0, u8 *a1, u8 *a2);
f32 func_0029DFD0(f32 *a0);
void sceVu0Normalize(f32 *a0, f32 *a1);
f32 atan2f(f32 y, f32 x);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 Mathf_Asin(f32 farg0);
extern f32 D_00385A9C;
extern f32 D_00385AA0;

void func_00215CA8(s32 arg0, u8 *arg1, f32 farg0, f32 farg1) {
    f32 vec[4];
    u8 *s1;
    f32 f12;
    f32 f13;
    f32 w;
    f32 aw;

    s1 = BtlChar_GetPos(arg0, arg1, farg0, farg1);
    func_00312650(vec, arg1, s1);
    f12 = farg0;
    f13 = farg1;
    if (D_00385A9C < func_0029DFD0(vec)) {
        sceVu0Normalize(vec, vec);
        f12 = vec[0];
    }
    if (D_00385A9C < (f12 < 0.0f ? -f12 : f12)) {
        *(f32 *)(s1 + 0xB4) = atan2f(f12, f13);
    } else {
        f13 = vec[2];
        if (D_00385A9C < (f13 < 0.0f ? -f13 : f13)) {
            *(f32 *)(s1 + 0xB4) = atan2f(f12, f13);
        } else {
            *(s32 *)(s1 + 0xB4) = 0;
        }
    }
    w = BtlUtil_WrapAngle(*(f32 *)(s1 + 0xB4) - *(f32 *)(s1 + 0x14));
    aw = w < 0.0f ? -w : w;
    f13 = aw * farg1;
    if (f13 < D_00385AA0) {
        f13 = D_00385AA0;
    }
    if (farg0 < f13) {
        f13 = farg0;
    }
    if (w < -f13) {
        *(f32 *)(s1 + 0x14) = BtlUtil_WrapAngle(*(f32 *)(s1 + 0x14) - f13);
    } else if (f13 < w) {
        *(f32 *)(s1 + 0x14) = BtlUtil_WrapAngle(*(f32 *)(s1 + 0x14) + f13);
    } else {
        *(f32 *)(s1 + 0x14) = *(f32 *)(s1 + 0xB4);
    }
    f12 = vec[1];
    if (f12 < -1.0f) {
        f12 = -1.0f;
    }
    if (1.0f < f12) {
        f12 = 1.0f;
    }
    w = Mathf_Asin(f12);
    *(s32 *)(s1 + 0xB8) = 0;
    *(f32 *)(s1 + 0xB0) = -w;
    *(s32 *)(s1 + 0xBC) = 0;
}
