#include "common.h"

extern f32 D_003864BC;
extern f32 D_003864C0;
extern f32 D_003864C4;
extern f32 D_003864C8;
extern f32 D_003864CC;
extern f32 D_003864D0;
extern f32 D_003864D4;
extern f32 D_003864D8;
extern f32 D_003864DC;
extern f32 D_003864E0;
extern f32 D_003864E4;

s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
f32 func_00240D50(u8 *a0, s32 a1);
s32 func_00240E50(u8 *a0, s32 a1);
s32 BtlObjXf_Update(u8 *a0);
void func_001FA0A0(u8 *a0, s32 a1, s32 a2);
void func_001FA110(u8 *a0, s32 a1);
s32 func_00217488(u8 *a0);
s32 func_00217BD0(u8 *a0);
void func_001F9D78(u8 *a0, s32 a1);
void func_001F9D68(u8 *a0, f32 f12);
void func_001F9D10(u8 *a0, s32 a1);
void func_001F9FB0(u8 *a0, s32 a1);
s32 func_001FA2E0(u8 *a0);
f32 func_001FA318(u8 *a0);
s32 BtlPad_Test4C(u8 *a0, s32 a1);
u8 *BtlChar_GetPos(u8 *a0);
u8 *BtlMember_GetActiveGauge(u8 *a0);
f32 func_00240ED8(u8 *a0, s32 a1);
f32 func_00240F18(u8 *a0, s32 a1);
void func_00215550(u8 *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(u8 *a0, s32 a1, f32 f12);
void func_00216208(u8 *a0, f32 f12, f32 f13);
void BtlMove_BrakeVertical(u8 *a0);
void func_00216678(u8 *a0);
void func_0020D7E8(u8 *a0, f32 f12, f32 f13);
f32 BtlOpp_GetPitchAdjusted(u8 *a0);
void func_002181F0(u8 *a0, f32 f12);
f32 atan2f(f32 y, f32 x);
f32 sinf(f32 x);
f32 BtlUtil_WrapAngle(f32 x);
s32 func_00206958(u8 *a0, s64 a1);

s32 func_0022A6D0(u8 *s1) {
    f32 f20, f21, f22 = 0.0f, f23, f24;
    s32 s0, s2, v0, v1;
    u8 *p0, *p1;

    f23 = f22;
    if (func_00211310(s1, 0, 0x100)) {
        f24 = func_00240D50(s1, 5);
        s0 = func_00240E50(s1, 3);
        s2 = func_00240E50(s1, 2);
    } else {
        f24 = func_00240D50(s1, 4);
        s0 = func_00240E50(s1, 1);
        s2 = func_00240E50(s1, 0);
    }
    v1 = BtlObjXf_Update(s1);
    if (v1 == 0x18) {
        func_001FA110(s1, 0);
        v0 = func_00217488(s1);
        f22 = D_003864C0;
        f23 = f24;
        if (v0 == 0xE) {
            if (!func_00211310(s1, 0, 1)) {
                func_001F9D78(s1, 0x19);
            } else if (!func_00211310(s1, 0, 2)) {
                if (func_00211310(s1, 4, 0x80)) func_001F9D78(s1, 0x19);
            }
        }
        v1 = *(s32 *)(s1 + 0x8CC);
        if (s2 < v1) {
            func_001F9D78(s1, 0x19);
        } else if (s0 < v1 && BtlPad_Test4C(s1, 3)) {
            func_001F9D78(s1, 0x20);
        } else if (func_00217BD0(s1)) {
            func_001F9D78(s1, 0x19);
            f23 = 0.0f;
            *(f32 *)(BtlChar_GetPos(s1) + 0xC0) = f23;
        }
        func_00206958(s1, 0x1000);
        if (func_00211310(s1, 0, 4)) func_00206958(s1, 0x200000000LL);
    } else if (v1 < 0x19) {
        if (v1 == 0x17) {
            func_001FA0A0(s1, 0x18, 0);
            f23 = f24;
            f22 = D_003864BC;
            if (s0 < *(s32 *)(s1 + 0x8CC)) {
                if (BtlPad_Test4C(s1, 3)) func_001F9D78(s1, 0x20);
            }
            func_00206958(s1, 0x1000);
            if (func_00211310(s1, 0, 4)) func_00206958(s1, 0x200000000LL);
        }
    } else if (v1 == 0x19) {
        f23 = 0.0f;
        if (!func_00211310(s1, 0, 2)) {
            f22 = D_003864C4;
            if (!func_00211310(s1, 1, 4)) f22 = D_003864C8;
        } else {
            f22 = D_003864CC;
        }
        func_001F9FB0(s1, 0);
        if (func_00211310(s1, 0, 4)) func_002113C0(s1, 0, 2, 0);
        if (BtlPad_Test4C(s1, 3)) func_001F9D78(s1, 0x20);
    } else if (v1 == 0x20) {
        func_001F9FB0(s1, 0);
        f23 = 0.0f;
        f22 = D_003864D0;
        if (func_001FA2E0(s1) && func_00211310(s1, 0, 4)) func_00206958(s1, 0x400000000LL);
        if (func_00217BD0(s1)) *(s32 *)(BtlChar_GetPos(s1) + 0xC0) = 0;
        if (func_00211310(s1, 0, 4)) func_002113C0(s1, 0, 2, 0);
    }

    s2 = -1;
    p0 = BtlChar_GetPos(s1);
    p1 = BtlChar_GetPos(s1);
    f20 = BtlUtil_WrapAngle(atan2f(*(f32 *)(p0 + 0x20), *(f32 *)(p1 + 0x28)) - *(f32 *)(s1 + 0x150));
    f21 = __builtin_fabsf(sinf(f20));
    if (f20 < 0.0f) {
        v1 = BtlObjXf_Update(s1);
        if (v1 == 0x18) s2 = 0x1B;
        else if (v1 < 0x19) { if (v1 == 0x17) s2 = 0x1A; }
        else if (v1 == 0x19) s2 = 0x1C;
    } else {
        v1 = BtlObjXf_Update(s1);
        if (v1 == 0x18) s2 = 0x1E;
        else if (v1 < 0x19) { if (v1 == 0x17) s2 = 0x1D; }
        else if (v1 == 0x19) s2 = 0x1F;
    }
    if (s2 >= 0) {
        func_001F9D68(s1, f21);
        func_001F9D10(s1, s2);
    }
    if (func_00217488(s1) == 0xE && func_00211310(s1, 0, 1)) {
        f21 = func_00240ED8(s1, 0);
        f20 = func_00240F18(s1, 0);
        v0 = func_00211310(s1, 0, 2);
        func_00215550(s1, v0, f24, f21, 0.0f, f20, 0.0f, D_003864D4, D_003864D8);
    } else {
        func_00215068(s1, 5, 0xC, D_003864DC, D_003864E0);
    }
    func_00215E88(s1, 3, D_003864E4);
    func_00216208(s1, f23, f22);
    if (func_00211310(s1, 1, 4)) {
        BtlMove_BrakeVertical(s1);
        v1 = *(s32 *)(s1 + 0x8E4);
        if (v1 == 0x19 || v1 == 0x20) {
            *(s32 *)(s1 + 0x8DC) = *(s32 *)(s1 + 0x8DC) | 2;
        }
    } else {
        func_00216678(s1);
    }
    func_0020D7E8(s1, 20.0f, 50.0f);
    if (func_00211310(s1, 0, 1) && func_00217488(s1) == 0xE && func_00211310(s1, 0, 2)) {
        f21 = 0.0f;
        v1 = BtlObjXf_Update(s1);
        if (v1 == 0x18) {
            f21 = 1.0f;
        } else if (v1 < 0x19) {
            if (v1 == 0x17) f21 = func_001FA318(s1);
        } else if (v1 == 0x19 || v1 == 0x20) {
            f21 = 1.0f - func_001FA318(s1);
        }
        f20 = BtlOpp_GetPitchAdjusted(s1);
        if (0.0f < f20) f20 = f20 * 0.5f;
        p0 = BtlChar_GetPos(s1);
        *(f32 *)(p0 + 0xD4) = f20 * f21;
        func_002181F0(s1, 10.0f);
    }
    if (func_00217488(s1) == 0xE) {
        func_002113C0(s1, 1, 0x800000, 1);
    } else {
        func_002113C0(s1, 1, 0x40, 1);
    }
    if (func_00211310(s1, 0, 0x100)) func_002113C0(s1, 0, 2, 1);
    if (BtlMember_GetActiveGauge(s1)[0x29]) func_002113C0(s1, 6, 8, 1);
    return func_00206958(s1, 0x80000000000LL);
}
