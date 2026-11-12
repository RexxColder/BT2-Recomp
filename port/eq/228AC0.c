#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlObjXf_Update(s32 arg0);
u8 *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 arg0);
void func_001F9DB8(s32 arg0, s32 arg1);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
extern f32 atan2f(f32 y, f32 x);
extern f32 sinf(f32 x);
void func_001F9D68(s32 arg0, f32 farg0);
void func_001F9D10(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
f32 func_00240D50(s32 arg0, s32 arg1);
void func_001FA110(s32 arg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_GetCountFC(s32 arg0, s32 arg1);
s32 func_001F9D78(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
f32 func_00207E88(s32 arg0);
void BtlOpp_GetDelta(s32 arg0, f32 *arg1);
f32 sceVu0InnerProduct(f32 *a, f32 *b);
void sceVu0Normalize(f32 *dst, f32 *src);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_002166C0(s32 arg0);
void func_00216678(s32 arg0);
void func_0020D7E8(s32 arg0, f32 farg0, f32 farg1);
u8 *BtlMember_GetActiveGauge(s32 arg0);
extern f32 D_003863C4, D_003863C8, D_003863CC, D_003863D0, D_003863D4, D_003863D8, D_003863DC;
extern f32 D_003863E0, D_003863E4, D_003863E8, D_003863EC, D_003863F0, D_003863F4;

s32 func_00228AC0(u8 *obj) {
    f32 delta[4];
    f32 dir[4];
    f32 *speedp;
    f32 ang, target, dist, fwd, dotv, t;
    s32 changed, st, flagv, o;
    u8 *pos0, *pos1, *gauge;

    o = (s32)obj;
    speedp = (f32 *)(obj + 0x8D0);
    fwd = 0.0f;
    if (func_00211310(o, 0, 4)) {
        func_002113C0(o, 0, 2, 0);
    }
    if (BtlObjXf_Update(o) != 0x1A4) {
        changed = 0;
        pos0 = BtlChar_GetPos(o);
        pos1 = BtlChar_GetPos(o);
        ang = atan2f(*(f32 *)(pos0 + 0x20), *(f32 *)(pos1 + 0x28));
        target = BtlUtil_WrapAngle(ang - *(f32 *)(obj + 0x150));
        if (D_003863C4 < target && target < D_003863C8) {
            st = BtlObjXf_Update(o);
            if (st == 15) {
                func_001F9DB8(o, 12);
                changed = 1;
            } else if (st >= 16) {
                if (st == 16) {
                    func_001F9DB8(o, 13);
                    changed = 1;
                }
            } else if (st == 14) {
                func_001F9DB8(o, 11);
                changed = 1;
            }
        } else {
            st = BtlObjXf_Update(o);
            if (st == 12) {
                func_001F9DB8(o, 15);
                changed = 1;
            } else if (st >= 13) {
                if (st == 13) {
                    func_001F9DB8(o, 16);
                    changed = 1;
                }
            } else if (st == 11) {
                func_001F9DB8(o, 14);
                changed = 1;
            }
        }
        if (changed) {
            BtlAnim_SetBlend(o, D_003863CC);
        }
        t = sinf(target);
        if (*speedp < t) {
            *speedp = *speedp + D_003863D0;
            if (t < *speedp) {
                *speedp = t;
            }
        } else {
            *speedp = *speedp - D_003863D4;
            if (*speedp < t) {
                *speedp = t;
            }
        }
        if (0.0f < *speedp) {
            func_001F9D68(o, *speedp);
            switch (BtlObjXf_Update(o)) {
            case 11:
            case 14:
                func_001F9D10(o, 0x14);
                break;
            case 12:
            case 15:
                func_001F9D10(o, 0x15);
                break;
            case 13:
            case 16:
                func_001F9D10(o, 0x16);
                break;
            }
        } else {
            func_001F9D68(o, -*speedp);
            switch (BtlObjXf_Update(o)) {
            case 11:
            case 14:
                func_001F9D10(o, 0x11);
                break;
            case 12:
            case 15:
                func_001F9D10(o, 0x12);
                break;
            case 13:
            case 16:
                func_001F9D10(o, 0x13);
                break;
            }
        }
    }
    st = BtlObjXf_Update(o);
    if (st == 14 || st == 11) {
        if (func_001FA0A0(o, BtlObjXf_Update(o) + 1, 0)) {
            BtlAnim_SetBlend(o, D_003863D8);
        }
        fwd = func_00240D50(o, func_00211310(o, 0, 0x100) ? 3 : 2);
    } else if (st == 12 || st == 15) {
        func_001FA110(o, 0);
        fwd = func_00240D50(o, func_00211310(o, 0, 0x100) ? 3 : 2);
        if (!BtlPad_Test48(o, 8) && BtlPad_GetCountFC(o, 8) >= 3) {
            func_001F9D78(o, BtlObjXf_Update(o) + 1);
            BtlAnim_SetBlend(o, D_003863DC);
        }
        if ((func_0023F410(o) & 0x1000) != 0 && func_00211310(o, 0, 2)) {
            if (!func_00211310(o, 0, 0x100)) {
                BtlAnim_SetBlend(o, D_003863E0);
                func_001F9D78(o, 0x1A4);
            }
        }
    } else if (st == 13 || st == 16) {
        func_001F9FB0(o, 0);
        if (BtlPad_Test48(o, 8)) {
            t = func_00207E88(o);
            func_001F9D78(o, (0.0f < t) ? 0xE : 0xB);
            BtlAnim_SetBlend(o, D_003863E4);
        }
        fwd = 0.0f;
    } else if (st == 0x1A4) {
        func_001FA110(o, 0);
        fwd = func_00240D50(o, func_00211310(o, 0, 0x100) ? 3 : 2);
        if (func_00211310(o, 0, 0x104)) {
            BtlAnim_SetBlend(o, D_003863E8);
            if (func_00207E88(o) < 0.0f) {
                func_001F9D78(o, 0xB);
            } else {
                func_001F9D78(o, 0xE);
            }
        }
    }
    BtlOpp_GetDelta(o, delta);
    delta[1] = 0.0f;
    dist = __builtin_sqrtf(delta[0] * delta[0] + delta[2] * delta[2]);
    if (dist < 30.0f) {
        sceVu0Normalize(dir, (f32 *)(BtlChar_GetPos(o) + 0x30));
        dir[1] = 0.0f;
        dotv = sceVu0InnerProduct(dir, delta);
        t = dotv / dist;
        if (t < 0.0f) {
            t = -t;
        }
        fwd = fwd * t + fwd * (1.0f - t) * (dist / 30.0f);
    }
    flagv = func_00211310(o, 0, 2) != 0;
    func_00215068(o, 1, 10, D_003863F0, D_003863EC);
    func_00215E88(o, flagv, D_003863EC);
    func_00216208(o, fwd, D_003863F4);
    if (BtlObjXf_Update(o) == 0x1A4) {
        func_002166C0(o);
    } else {
        func_00216678(o);
    }
    func_0020D7E8(o, 10.0f, 20.0f);
    func_002113C0(o, 9, 0x40, 1);
    func_002113C0(o, 1, 0x400, 1);
    func_002113C0(o, 1, 0x400000, 1);
    gauge = BtlMember_GetActiveGauge(o);
    if (*(u8 *)(gauge + 0x29)) {
        return func_002113C0(o, 6, 8, 1);
    }
    return (s32)gauge;
}
