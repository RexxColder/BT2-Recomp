#include "common.h"

extern f32 D_00383E80;
extern f32 D_00383E84;
extern f32 D_00383E88;
extern f32 D_00383E8C;
extern f32 D_00383E90;
extern f32 D_00383E94;
extern f32 D_00383E98;

s32 func_00203D08(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001106D8(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0020C5A8(s32 arg0);
f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(s32 arg0);
void func_00113860(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(s32 arg0, s32 arg1);
void func_00113B00(s32 arg0, s32 arg1, s32 arg2);
void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);

void func_00110898(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s0;
    f32 ratio;
    f32 f;
    s32 v;
    s32 r;

    s1 = (u8 *)func_00203D08(arg2);
    s3 = (u8 *)func_0010B0A0(arg1);
    s2 = arg0 + arg1 * 0x750;
    s4 = s3 + 0x3180;
    func_00114508((s32)s4, 2, 0, 0xC);

    ratio = (f32)*(s32 *)(s1 + 4);
    ratio = (f32)*(s32 *)(s1 + 0) / ratio;
    s1 = s2 + 0xD0;
    func_001106D8(ratio, (s32)s4, 0, 0x34, 0x44);

    v = func_0020C5A8(arg2);
    ratio = (f32)v / D_00383E80;
    func_001106D8(ratio, (s32)(s3 + 0x3360), 1, 0x34, 0x4A);

    v = func_0020C5A8(arg2);
    if (v != 100000) {
        *(s32 *)(s1 + 0x734) = 0;
    } else {
        if (*(s32 *)(s1 + 0x734) != 0) {
            s2 += 0x144;
            if (Ramp_Step((s32)s2) != 0) {
                if (*(f32 *)(s1 + 0x84) == 1.0f) {
                    Ramp_Start((s32)s2, D_00383E8C, 1.0f, D_00383E90);
                } else {
                    Ramp_Start((s32)s2, D_00383E94, D_00383E98, 1.0f);
                }
            }
        } else {
            Ramp_Start((s32)(s2 + 0x144), D_00383E84, 1.0f, D_00383E88);
            *(s32 *)(s1 + 0x734) = *(s32 *)(s1 + 0x734) + 1;
        }

        func_00113860((s32)(s4 + 0x3CC), 0, 0x2C, 0x40, 0x40, 0x12);
        s0 = s4 + 0x3C0;
        func_00113D80((s32)s0, 0);
        func_00113B00((s32)s0, 0x26, 0x44);

        /* cvt.w.s truncates toward zero (saturating): plain cast */
        f = *(f32 *)(s1 + 0x84) * 100.0f;
        if (f >= 2147483648.0f) {
            f = f - 2147483648.0f;
        }
        r = (s32)f;
        *(u8 *)(s4 + 0x3D9) = (u8)r;
    }

    if (arg1 == 1) {
        func_001140A8((s32)s4, 0, 1, 0, 0xC);
    }
    BtlRec_CallFlagged((s32)s4, 1, 0xC);
}
