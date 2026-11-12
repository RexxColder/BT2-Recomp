#include "common.h"

extern f32 D_0038695C, D_00386960, D_00386964, D_00386968, D_0038696C, D_00386970;
extern f32 D_00386974, D_00386978, D_0038697C, D_00386980, D_00386984, D_00386988;
extern f32 D_0038698C, D_00386990, D_00386994;

extern u32 func_00212320(u8 *o);
extern s32 BtlObjXf_Update(u8 *o);
extern s32 func_001FA0A0(u8 *o, s32 a1, s32 a2);
extern s32 func_001FA2E0(u8 *o);
extern void func_00230BB0(u8 *o, s32 a1);
extern void func_00230C48(u8 *o);
extern void func_00230C60(u8 *o, s32 a1);
extern void func_002113C0(u8 *o, s32 a1, s32 a2, s32 a3);
extern void BtlChar_Vibrate(u8 *o, f32 a, f32 b);
extern void func_001FCD80(u8 *o);
extern s32 func_00206958(u8 *o, s64 a1);
extern void func_001FA110(u8 *o, s32 a1);
extern void BtlChar_SetSmallVibration(u8 *o, f32 a);
extern u8 *BtlChar_GetPos(u8 *o);
extern f32 func_0029DFD0(u8 *p);
extern s32 func_001F9D78(u8 *o, s32 a1);
extern f32 func_00241218(u8 *o, s32 a1);
extern s32 func_00211310(u8 *o, s32 a1, s32 a2);
extern s32 func_001F9FB0(u8 *o, s32 a1);
extern f32 func_00241B90(u8 *o, s32 a1);
extern void func_00215068(u8 *o, s32 a1, s32 a2, f32 a, f32 b);
extern f32 func_00240ED8(u8 *o, s32 a1);
extern f32 func_00240F18(u8 *o, s32 a1);
extern void func_00215550(u8 *o, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
extern void func_00215E88(u8 *o, s32 a1, f32 a);
extern void func_00216208(u8 *o, f32 a, f32 b);
extern void func_00216678(u8 *o);
extern s32 func_002411E0(u8 *o, s32 a1);
extern f32 func_001FA318(u8 *o);
extern void func_002181F0(u8 *o, f32 a);
extern void func_00231188(u8 *o, s32 a1, s32 a2);

/* Per-frame state handler for a character in the 284..386 state block (three copies 34 apart, plus state 386).
   Runs the per-state transition, then the common part (blend/anim/flag updates) and tail-calls 0x231188. */
void func_00234720(u8 *o) {
    s32 *cnt0 = (s32 *)(o + 0x8C0);
    s32 *cnt1 = (s32 *)(o + 0x8C4);
    s32 active = 0;
    s32 st;
    u32 idx;
    s32 tmp;
    f32 f20, f21, f22, f23, fr;

    st = func_00212320(o);
    idx = BtlObjXf_Update(o) - 0x11C;
    if (idx < 0x67) {
        switch (idx) {
        case 0x66:
            func_001FA0A0(o, 0x160, 0);
            if (func_001FA2E0(o)) {
                func_00230C48(o);
            }
            goto common_a;
        case 0: case 34: case 68:
            tmp = BtlObjXf_Update(o);
            func_001FA0A0(o, tmp + 1, 0);
            if (func_001FA2E0(o)) {
                func_00230BB0(o, st);
            }
            goto common_a;
        case 1: case 35: case 69:
            tmp = BtlObjXf_Update(o);
            func_001FA0A0(o, tmp + 1, 0);
        common_a:
            func_00230C60(o, 0);
            func_002113C0(o, 9, 4, 1);
            break;
        case 2: case 36: case 70:
            tmp = BtlObjXf_Update(o);
            func_001FA0A0(o, tmp + 1, 0);
            if (func_001FA2E0(o)) {
                BtlChar_Vibrate(o, D_0038695C, D_00386960);
                func_002113C0(o, 0xE, 0x200, 1);
                func_001FCD80(o);
            }
            func_00206958(o, 8);
            func_00206958(o, (s64)0x8000 << 28);
            func_002113C0(o, 1, 0x2000, 1);
            func_002113C0(o, 7, 0x80000, 1);
            if (*(u32 *)(o + 0x8DC) & 1) {
                func_002113C0(o, 3, 0x200, 1);
            }
            active = 1;
            break;
        case 3: case 37: case 71:
            func_001FA110(o, 0);
            active = 1;
            func_002113C0(o, 3, 0x200, 1);
            func_002113C0(o, 7, 0x80000, 1);
            func_00206958(o, 8);
            func_00206958(o, (s64)0x8000 << 28);
            func_002113C0(o, 1, 0x2000, 1);
            BtlChar_SetSmallVibration(o, D_00386964);
            if (func_0029DFD0(BtlChar_GetPos(o) + 0x50) < D_00386968) {
                tmp = *cnt0 + 1;
                *cnt0 = tmp;
                if (tmp >= 0x10) {
                    active = 0;
                    func_001F9D78(o, BtlObjXf_Update(o) + 3);
                    *(s32 *)(BtlChar_GetPos(o) + 0xC0) = 0;
                }
            } else {
                *cnt0 = 0;
            }
            tmp = *cnt1 + 1;
            f20 = (f32)tmp;
            *cnt1 = tmp;
            if (func_00241218(o, st) * 30.0f < f20) {
                active = 0;
                func_001F9D78(o, BtlObjXf_Update(o) + 3);
                *(s32 *)(BtlChar_GetPos(o) + 0xC0) = 0;
            }
            if (!func_00211310(o, 0, 1)) {
                active = 0;
                func_001F9D78(o, BtlObjXf_Update(o) + 3);
            }
            if (func_00211310(o, 4, 0x1000000)) {
                active = 0;
                func_001F9D78(o, BtlObjXf_Update(o) + 3);
                *(s32 *)(BtlChar_GetPos(o) + 0xC0) = 0;
            }
            break;
        case 6: case 40: case 74:
            func_001F9FB0(o, 0);
            break;
        default:
            break;
        }
    }

    if (active) {
        f23 = func_00241B90(o, st);
        if (*(u32 *)(o + 0x8DC) & 1) {
            func_00215068(o, 5, 0xD, D_0038696C, D_00386970);
        } else {
            f22 = func_00240ED8(o, 3);
            f21 = func_00240ED8(o, 4);
            f20 = func_00240F18(o, 3);
            fr = func_00240F18(o, 4);
            func_00215550(o, 1, f23, f22, f21, f20, fr, D_00386974, D_00386978);
        }
        func_00215E88(o, 3, D_0038697C);
        func_00216208(o, f23, D_00386980);
    } else {
        f20 = D_00386984;
        func_00215068(o, 5, 0xD, D_00386988, f20);
        func_00215E88(o, 7, f20);
        func_00216208(o, 0.0f, D_0038698C);
    }
    func_00216678(o);
    func_002113C0(o, 0xD, 8, 1);
    func_002113C0(o, 0xD, 0x10, 1);
    func_002113C0(o, 0xD, 1, 1);
    if (!(func_002411E0(o, st) & 0x10)) {
        func_00206958(o, 0x8000);
    }
    func_002113C0(o, 1, 0x800000, 1);
    if (*(u32 *)(o + 0x8DC) & 1) {
        func_002113C0(o, 1, 0x40, 1);
    }
    if (func_00211310(o, 0, 1)) {
        if (func_002411E0(o, st) >= 0) {
            f21 = 0.0f;
            idx = BtlObjXf_Update(o) - 0x11C;
            if (idx < 0x67) {
                switch (idx) {
                case 2: case 36: case 70:
                    f21 = func_001FA318(o);
                    break;
                case 3: case 37: case 71:
                    f21 = 1.0f;
                    break;
                case 6: case 40: case 74:
                    f21 = 1.0f - func_001FA318(o);
                    break;
                default:
                    break;
                }
            }
            f20 = *(f32 *)(BtlChar_GetPos(o) + 0xB0);
            if (f20 < D_00386990) {
                f20 = D_00386990;
            }
            if (D_00386994 < f20) {
                f20 = D_00386994;
            }
            *(f32 *)(BtlChar_GetPos(o) + 0xD4) = f20 * f21;
            func_002181F0(o, 10.0f);
        }
    }
    func_00231188(o, st, *(s32 *)(o + 0x8CC));
}
