#include "common.h"

extern f32 D_00386A88;
extern f32 D_00386A8C;
extern f32 D_00386A90;
extern f32 D_00386A94;
extern f32 D_00386A98;
extern f32 D_00386A9C;
extern f32 D_00386AA0;
extern f32 D_00386AA4;
extern f32 D_00386AA8;
extern f32 D_00386AAC;
extern f32 D_00386AB0;
extern f32 D_00386AB4;

s32 BtlObjXf_Update(void *arg0);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
void BtlChar_Vibrate(void *arg0, f32 farg0, f32 farg1);
f32 func_001FA318(void *arg0);
void BtlMove_BrakeVertical(void *arg0);
void func_00216890(void *arg0, f32 farg0, f32 farg1);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FA110(void *arg0, s32 arg1);
void func_00206958(void *arg0, s64 arg1);
void BtlChar_SetVibration(void *arg0, f32 farg0, f32 farg1);
f32 func_00217360(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_00212878(void);
s32 func_0023F410(void *arg0);
s32 EftWater_GetSurfaceY(void *arg0);
u8 *BtlChar_GetPos(void *arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_001F9D78(void *arg0, s32 arg1);
s32 func_001F9FB0(void *arg0, s32 arg1);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(void *arg0, s32 arg1, f32 farg0);
void func_00216208(void *arg0, f32 farg0, f32 farg1);

void func_00237EC0(void *arg0) {
    u8 *s0;
    u8 *s3;
    u8 *pos;
    f32 sp[4];
    s32 s1;
    s32 s2;
    s32 v0;
    s32 v1;
    f32 f0;
    f32 f20;

    s0 = (u8 *)arg0;
    s3 = s0 + 0x8C0;
    v1 = BtlObjXf_Update(s0);
    if (v1 == 0xA7) {
        goto l80e0;
    }
    if (v1 < 0xA8) {
        if (v1 == 0xA5) {
            goto l7f28;
        }
        goto l80ec;
    }
    if (v1 == 0xA8) {
        goto l7fa8;
    }
    goto l80ec;

l7f28:
    v0 = func_001FA0A0(s0, 0xA8, 1);
    if (v0 != 0) {
        BtlChar_Vibrate(s0, D_00386A88, D_00386A8C);
    }
    f0 = func_001FA318(s0);
    if (f0 < D_00386A90) {
        BtlMove_BrakeVertical(s0);
    } else {
        func_00216890(s0, D_00386A94, D_00386A98);
    }
    func_002113C0(s0, 5, 0x20, 1);
    goto l80ec;

l7fa8:
    func_001FA110(s0, 0);
    s2 = 0;
    func_00216890(s0, D_00386A9C, D_00386AA0);
    func_002113C0(s0, 5, 0x20, 1);
    BtlChar_SetVibration(s0, D_00386AA4, D_00386AA8);
    func_00206958(s0, 8);
    *(s32 *)s3 = *(s32 *)s3 + 1;
    f0 = func_00217360(s0);
    if (f0 < 2.0f) {
        s2 = 1;
    }

    /* l801c */
    s1 = 1;
    v0 = func_00211310(s0, 0, 0x20);
    if (v0 != 0) {
        s2 = s1;
    }
    v0 = func_00212878();
    if (v0 != 0) {
        v0 = func_00211310(s0, 0, 0x40);
        if (v0 != 0) {
            s2 = s1;
        }
    }

    /* l8050 */
    v1 = *(s32 *)s3;
    if (v1 >= 0xB) {
        v0 = (v1 < 0x5B);
        if (v0 == 0) {
            s2 = s1;
        }
        v0 = func_0023F410(s0);
        if ((v0 & 0x400) != 0) {
            if (EftWater_GetSurfaceY(sp) != 0) {
                pos = BtlChar_GetPos(s0);
                f0 = *(f32 *)(pos + 0x4);
                f20 = sp[0] - f0;
                f0 = BtlCharApi_GetHeight(*(s32 *)(s0 + 0x1534));
                f0 = f0 * 3.0f;
                if (f20 < f0) {
                    s2 = 1;
                }
            }
        }
    }

    /* l80bc */
    if (s2 != 0) {
        func_001F9D78(s0, 0xA7);
        pos = BtlChar_GetPos(s0);
        *(s32 *)(pos + 0xC4) = 0;
    }
    goto l80ec;

l80e0:
    func_001F9FB0(s0, 0);

l80ec:
    func_00215068(s0, 5, 0xC, D_00386AAC, 0.5f);
    func_00215E88(s0, 2, D_00386AB0);
    func_00216208(s0, 0.0f, D_00386AB4);
    func_002113C0(s0, 0xD, 1, 1);
    func_002113C0(s0, 1, 0x40, 1);
    func_002113C0(s0, 3, 0x800, 1);
    func_002113C0(s0, 3, 0xE, 1);
}
