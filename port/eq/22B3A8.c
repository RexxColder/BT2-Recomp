#include "common.h"

s32 func_00217488(s32 a0);
f32 func_00240D50(s32 a0, s32 a1);
s32 func_00240EA8(s32 a0, s32 a1);
s32 BtlObjXf_Update(s32 a0);
s32 func_001FA0A0(s32 a0, s32 a1, s32 a2);
s32 func_001F9FB0(s32 a0, s32 a1);
s32 func_00217BD0(s32 a0);
s32 func_001FA110(s32 a0, s32 a1);
s32 func_001F9D78(s32 a0, s32 a1);
s32 func_00211310(s32 a0, s32 a1, s32 a2);
s32 func_00203888(s32 a0, s32 a1, s32 a2);
void func_00206958(s32 a0, s64 a1);
s32 func_002113C0(s32 a0, s32 a1, s32 a2, s32 a3);
void func_0020FC38(s32 a0, s32 a1);
s32 func_0023F410(s32 a0);
f32 func_0029DFD0(s32 a0);
void func_00215550(s32 a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
void func_00215068(s32 a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(s32 a0, s32 a1, f32 f12);
void func_00216208(s32 a0, f32 f12, f32 f13);
void func_00216678(s32 a0);
void func_00216890(s32 a0, f32 f12, f32 f13);
f32 func_001FA318(s32 a0);
void func_002181F0(s32 a0, f32 f12);
void func_0020D7E8(s32 a0, f32 f12, f32 f13);
f32 func_00240ED8(s32 a0, s32 a1);
f32 func_00240F18(s32 a0, s32 a1);
s32 BtlChar_GetPos(s32 a0);
void BtlAnim_SetBlend(s32 a0, f32 f12);
void BtlChar_Vibrate(s32 a0, f32 f12, f32 f13);
void BtlChar_SetVibration(s32 a0, f32 f12, f32 f13);
s32 BtlPad_Test4C(s32 a0, s32 a1);
s32 BtlPad_Test48(s32 a0, s32 a1);
extern f32 D_00386520, D_00386524, D_00386528, D_0038652C, D_00386530, D_00386534, D_00386538;
extern f32 D_0038653C, D_00386540, D_00386544, D_00386548, D_0038654C, D_00386550, D_00386554;
extern f32 D_00386558, D_0038655C, D_00386560, D_00386564, D_00386568, D_0038656C, D_00386570;
extern f32 D_00386574, D_00386578, D_0038657C, D_00386580, D_00386584, D_00386588, D_0038658C;

s32 func_0022B3A8(s32 obj) {
    s32 *counter = (s32 *)(obj + 0x8C0);
    s32 mode = 3;
    s32 flag = 0;
    f32 f26 = 0.0f;
    f32 f24 = 0.0f;
    f32 f23, f25, f20, f21, f22;
    s32 sv;

    if (func_00217488(obj) == 16) {
        f25 = func_00240D50(obj, 6);
        sv = func_00240EA8(obj, 0);
    } else {
        f25 = func_00240D50(obj, 7);
        sv = func_00240EA8(obj, 1);
    }
    f23 = 1.0f;

    switch (BtlObjXf_Update(obj)) {
    case 0x20:
        func_001F9FB0(obj, 0);
        f26 = 0.0f;
        f24 = D_00386570;
        f23 = 1.0f;
        mode = 7;
        if (func_00217BD0(obj)) {
            *(f32 *)(BtlChar_GetPos(obj) + 0xC0) = f26;
        }
        break;
    case 0x23:
        if (func_001FA0A0(obj, 0x24, 0)) {
            BtlAnim_SetBlend(obj, D_00386534);
            BtlChar_Vibrate(obj, D_00386538, D_0038653C);
            if (func_0023F410(obj) & 0x10) {
                func_0020FC38(obj, 0x1D);
            } else {
                func_0020FC38(obj, 0x1C);
            }
            func_002113C0(obj, 0xE, 0x200, 1);
        }
        if (func_00217488(obj) == 16) {
            func_002113C0(obj, 7, 0x80000, 1);
        }
        f26 = 0.0f;
        mode = 7;
        f24 = D_00386540;
        f23 = D_00386544;
        flag = 1;
        break;
    case 0x24:
        func_001FA110(obj, 0);
        f26 = f25;
        func_002113C0(obj, 1, 0x2000, 1);
        mode = 3;
        f24 = D_00386560;
        flag = 1;
        BtlChar_SetVibration(obj, D_00386558, D_0038655C);
        f23 = 1.0f;
        if (!(func_0023F410(obj) & 0x2000)) {
            func_002113C0(obj, 3, 0x40, 1);
        }
        if (func_0029DFD0(BtlChar_GetPos(obj) + 0x50) < D_00386564) {
            *counter = *counter + 1;
            if (*counter >= 16) {
                func_001F9D78(obj, 0x25);
                f26 = 0.0f;
                *(f32 *)(BtlChar_GetPos(obj) + 0xC0) = f26;
            }
        } else {
            *counter = 0;
        }
        if (func_00217488(obj) == 16) {
            if (!func_00211310(obj, 0, 1)) {
                func_001F9D78(obj, 0x25);
                flag = 0;
            }
        }
        if (BtlPad_Test4C(obj, 3)) {
            func_001F9D78(obj, 0x20);
            BtlAnim_SetBlend(obj, D_00386568);
        }
        if (func_00217BD0(obj)) {
            func_001F9D78(obj, 0x25);
            f26 = 0.0f;
            *(f32 *)(BtlChar_GetPos(obj) + 0xC0) = f26;
        }
        if (func_00203888(obj, sv, 0)) {
            func_001F9D78(obj, 0x25);
        }
        func_002113C0(obj, 0xD, 8, 1);
        func_00206958(obj, 8);
        func_00206958(obj, (s64)0x8000 << 28);
        if (func_00217488(obj) == 16) {
            func_00206958(obj, 0x400);
            func_002113C0(obj, 7, 0x80000, 1);
        }
        break;
    case 0x25:
        func_001F9FB0(obj, 0);
        f26 = 0.0f;
        f24 = D_0038656C;
        f23 = 1.0f;
        mode = 7;
        break;
    case 0x26:
        if (func_001FA0A0(obj, 0x24, 0)) {
            BtlAnim_SetBlend(obj, D_00386548);
        }
        func_00206958(obj, 8);
        func_00217488(obj);
        f26 = f25;
        f24 = D_0038654C;
        mode = 3;
        f23 = 1.0f;
        flag = 1;
        if (func_00217488(obj) == 16) {
            func_00206958(obj, 0x400);
        }
        func_002113C0(obj, 1, 0x2000, 1);
        BtlChar_SetVibration(obj, D_00386550, D_00386554);
        break;
    case 0x39:
        if (func_001FA0A0(obj, 0x26, 0)) {
            BtlAnim_SetBlend(obj, D_00386520);
            BtlChar_Vibrate(obj, D_00386524, D_00386528);
            if (func_0023F410(obj) & 0x10) {
                func_0020FC38(obj, 0x1D);
            } else {
                func_0020FC38(obj, 0x1C);
            }
            func_002113C0(obj, 0xE, 0x200, 1);
        }
        f26 = 0.0f;
        f24 = D_0038652C;
        f23 = D_00386530;
        mode = 7;
        break;
    default:
        break;
    }

    if (func_00217488(obj) == 16 && flag == 1) {
        f22 = func_00240ED8(obj, 1);
        f21 = func_00240ED8(obj, 2);
        f20 = func_00240F18(obj, 1);
        func_00215550(obj, 1, f25, f22, f21, f20, func_00240F18(obj, 2), D_00386574, f23);
    } else {
        func_00215068(obj, 5, 12, D_00386578, f23);
    }
    func_00215E88(obj, mode, D_0038657C);
    func_00216208(obj, f26, f24);
    if (BtlObjXf_Update(obj) == 0x24 && func_00217488(obj) != 16) {
        f20 = func_00240D50(obj, 8);
        if (BtlPad_Test48(obj, 4)) {
            func_00216890(obj, -f20, D_00386580);
        } else if (BtlPad_Test48(obj, 5)) {
            func_00216890(obj, f20, D_00386584);
        } else {
            func_00216678(obj);
        }
    } else {
        func_00216678(obj);
    }
    if (func_00211310(obj, 0, 1) && func_00217488(obj) == 16) {
        f21 = 0.0f;
        switch (BtlObjXf_Update(obj)) {
        case 0x39:
            f21 = 0.0f;
            break;
        case 0x23:
            f21 = func_001FA318(obj);
            break;
        case 0x26:
            f21 = func_001FA318(obj);
            f21 = f21 + f21;
            if (1.0f < f21) {
                f21 = 1.0f;
            }
            break;
        case 0x24:
            f21 = 1.0f;
            break;
        case 0x20:
        case 0x25:
            f21 = 1.0f - func_001FA318(obj);
            break;
        default:
            break;
        }
        f20 = *(f32 *)(BtlChar_GetPos(obj) + 0xB0);
        if (f20 < D_00386588) {
            f20 = D_00386588;
        }
        if (D_0038658C < f20) {
            f20 = D_0038658C;
        }
        *(f32 *)(BtlChar_GetPos(obj) + 0xD4) = f20 * f21;
        func_002181F0(obj, 10.0f);
    }
    func_0020D7E8(obj, 20.0f, 50.0f);
    func_002113C0(obj, 1, 0x800000, 1);
    func_002113C0(obj, 8, 4, 1);
    if (func_00217488(obj) == 16) {
        func_002113C0(obj, 5, 0x40, 1);
    }
    sv = func_00217488(obj);
    if (sv == 15) {
        return func_002113C0(obj, 1, 0x40, 1);
    }
    return sv;
}
