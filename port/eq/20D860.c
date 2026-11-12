#include "common.h"

extern f32 D_003859B8;

u8 *BtlChar_GetPos(s32 arg0);
void BtlChar_GetSnapPos(s32 arg0, s32 arg1, s32 arg2);
void BtlOpp_GetTargetPos(s32 arg0, s32 arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 Mathf_Acos(f32 farg0);
void Vec3_RotateY(f32 farg0, s32 arg0, s32 arg1);
f32 cosf(f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 func_0029DFD0(s32 arg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
f32 sceVu0InnerProduct(s32 arg0, s32 arg1);

void func_0020D860(u8 *arg0) {
    u8 sp[0x80];
    u8 *s2;
    u8 *p;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f0;
    f32 v;

    p = BtlChar_GetPos((s32)arg0);
    f20 = *(f32 *)(p + 0xCC);
    p = BtlChar_GetPos((s32)arg0);
    f22 = *(f32 *)(p + 0xD0);
    if (func_00211310((s32)arg0, 0, 1) == 0) {
        return;
    }
    if (func_00211310((s32)arg0, 1, 0x80) == 0) {
        return;
    }

    f23 = 1.0f;
    s2 = (u8 *)BtlChar_GetPos((s32)arg0);
    BtlChar_GetSnapPos((s32)arg0, (s32)(sp + 0x10), 0);
    func_003126C8((s32)sp, (s32)s2);
    BtlOpp_GetTargetPos((s32)arg0, (s32)(sp + 0x20));
    func_00312650((s32)(sp + 0x30), (s32)(sp + 0x20), (s32)(sp + 0x10));
    *(s32 *)(sp + 0x34) = 0;
    func_00312650((s32)(sp + 0x40), (s32)(sp + 0x20), (s32)sp);
    *(s32 *)(sp + 0x44) = 0;
    f21 = func_0029DFD0((s32)(sp + 0x30));
    f0 = func_0029DFD0((s32)(sp + 0x40));

    if (f22 < f0) {
        /* fall into the block below */
    } else if (f20 < f0) {
        f23 = (f0 - f20) / (f22 - f20);
    } else {
        return;
    }

    if (f21 < f20) {
        return;
    }
    f0 = sceVu0InnerProduct((s32)(sp + 0x30), (s32)(sp + 0x40));
    v = f0 / (f21 * f21);
    f22 = 1.0f;
    func_00312680(f22 - v, (s32)(sp + 0x60), (s32)(sp + 0x30));
    func_00312638((s32)(sp + 0x50), (s32)(sp + 0x40), (s32)(sp + 0x60));
    f20 = func_0029DFD0((s32)(sp + 0x50));
    if (f20 < D_003859B8) {
        return;
    }

    func_00312680(((f20 - f21) / f20) * f23, (s32)(sp + 0x70), (s32)(sp + 0x50));
    func_00312638((s32)s2, (s32)s2, (s32)(sp + 0x70));
    f0 = sceVu0InnerProduct((s32)(sp + 0x30), (s32)(sp + 0x50));
    v = f0 / (f21 * f20);
    if (f22 < v) {
        v = 1.0f;
    }
    f20 = Mathf_Acos(v);
    if (f23 < f22) {
        f20 = f20 * f23;
        cosf(f20);
    }
    if (((*(f32 *)(sp + 0x38) * *(f32 *)(sp + 0x50)) - (*(f32 *)(sp + 0x30) * *(f32 *)(sp + 0x58))) < 0.0f) {
        f20 = -f20;
    }
    Vec3_RotateY(f20, (s32)(s2 + 0x20), (s32)(s2 + 0x20));
    Vec3_RotateY(f20, (s32)(s2 + 0x30), (s32)(s2 + 0x30));
    *(f32 *)(s2 + 0x14) = BtlUtil_WrapAngle(*(f32 *)(s2 + 0x14) + f20);
    *(f32 *)(s2 + 0xB4) = BtlUtil_WrapAngle(*(f32 *)(s2 + 0xB4) + f20);
}
