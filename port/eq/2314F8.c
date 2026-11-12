#include "common.h"

extern f32 D_00386880, D_00386884, D_00386888, D_0038688C, D_00386890, D_00386894, D_00386898, D_0038689C;

extern u32 func_00212320(u8 *o);
extern s32 BtlObjXf_Update(u8 *o);
extern s32 func_00211310(u8 *o, s32 a1, s32 a2);
extern void func_002113C0(u8 *o, s32 a1, s32 a2, s32 a3);
extern f32 func_001FA340(u8 *o);
extern void func_001FA360(u8 *o, f32 f);
extern s32 func_001FA0A0(u8 *o, s32 a1, s32 a2);
extern s32 func_001FA2E0(u8 *o);
extern void func_00230BB0(u8 *o, s32 a1);
extern void func_00230C48(u8 *o);
extern void func_00230C60(u8 *o, s32 a1);
extern void func_001FA110(u8 *o, s32 a1);
extern void BtlChar_SetVibration(u8 *o, f32 a, f32 b);
extern s32 BtlPad_Test48(u8 *o, s32 a1);
extern s32 func_001F9D78(u8 *o, s32 a1);
extern s32 func_002411E0(u8 *o, s32 a1);
extern s32 **BtlMember_GetActiveGauge(u8 *o);
extern s32 func_00203310(u8 *o, s32 a1, s32 a2);
extern s32 func_00241778(u8 *o, s32 a1);
extern f32 func_001FA308(u8 *o);
extern s32 BtlObjAnim_QueryEvent(u8 *a, s32 b, s32 c, s32 d);
extern void func_001FCD80(u8 *o);
extern void func_00230D30(u8 *o, s32 a1, s32 a2);
extern void func_002310B8(u8 *o, s32 a1, s32 a2);
extern s32 func_00241170(u8 *o, s32 a1);
extern s32 func_001F9FB0(u8 *o, s32 a1);
extern void func_002177A8(u8 *o, s32 a1, s32 a2, s32 a3);
extern void func_00215068(u8 *o, s32 a1, s32 a2, f32 a, f32 b);
extern void func_00215E88(u8 *o, s32 a1, f32 a);
extern void func_00216208(u8 *o, f32 a, f32 b);
extern void func_00216678(u8 *o);
extern s32 func_00206958(u8 *o, s64 a1);

/* Per-frame handler for a character in the 284..386 state block (three copies 34 apart, plus state 386). */
void func_002314F8(u8 *o) {
    s32 *cnt = (s32 *)(o + 0x8C0);
    s32 active = 0;
    s32 doTail = 1;
    s32 st;
    s32 tmp;
    u32 idx;
    f32 f20, f0;

    st = func_00212320(o);
    idx = BtlObjXf_Update(o) - 0x11C;
    if (idx < 0x67) {
        switch (idx) {
        case 0x66:
            func_001FA0A0(o, 0x160, 0);
            if (func_001FA2E0(o)) {
                func_00230C48(o);
            }
            func_00230C60(o, 0);
            doTail = 0;
            if (!func_00211310(o, 7, 0x20000)) {
                func_002113C0(o, 9, 4, 1);
            }
            break;
        case 0: case 34: case 68:
            if (func_00211310(o, 7, 0x20000)) {
                f0 = func_001FA340(o);
                if (30.0f < f0) {
                    f20 = f0 / 30.0f;
                    func_001FA360(o, f20 + f20);
                }
            }
            tmp = BtlObjXf_Update(o);
            func_001FA0A0(o, tmp + 1, 0);
            if (func_001FA2E0(o)) {
                func_00230BB0(o, st);
            }
            func_00230C60(o, 0);
            active = 1;
            if (!func_00211310(o, 7, 0x20000)) {
                func_002113C0(o, 9, 4, 1);
            }
            break;
        case 1: case 35: case 69: {
            s32 leave;
            func_001FA110(o, 0);
            BtlChar_SetVibration(o, D_00386880, D_00386884);
            *cnt = *cnt + 1;
            if (func_00211310(o, 7, 0x20000)) {
                leave = (*cnt >= 0x1F);
                active = 1;
                if (!BtlPad_Test48(o, 1)) {
                    leave = 1;
                }
                if (leave) {
                    func_001F9D78(o, BtlObjXf_Update(o) + 1);
                    *cnt = 0;
                }
            } else {
                if (*cnt >= 0x97) {
                    func_002113C0(o, 7, 1, 1);
                }
                if (func_00211310(o, 7, 1)) {
                    func_001F9D78(o, BtlObjXf_Update(o) + 1);
                    *cnt = 0;
                }
            }
            func_00230C60(o, 0);
            active = 1;
            if (!func_00211310(o, 7, 0x20000)) {
                func_002113C0(o, 9, 4, 1);
            }
            break;
        }
        case 2: case 36: case 70:
            tmp = BtlObjXf_Update(o);
            if (func_001FA0A0(o, tmp + 1, 0)) {
                tmp = func_00212320(o);
                if (func_002411E0(o, tmp) & 0x400) {
                    s32 **g = BtlMember_GetActiveGauge(o);
                    func_00203310(o, **g - 1, 0x5B);
                    func_002113C0(o, 6, 0x10, 1);
                }
                tmp = func_00241778(o, st);
                if (func_00203310(o, tmp, 0x2F)) {
                    func_002113C0(o, 6, 4, 1);
                }
            }
            f20 = func_001FA308(o);
            tmp = BtlObjAnim_QueryEvent(*(u8 **)(o + 0x1530), 0x400, 0, 0);
            if (f20 < (f32)tmp) {
                func_00230C60(o, 1);
            }
            if (func_001FA2E0(o)) {
                func_001FCD80(o);
            }
            func_00230D30(o, st, 0);
            func_002310B8(o, st, 0);
            if (func_00241170(o, st)) {
                active = 1;
            }
            break;
        case 3: case 37: case 71:
            func_001FA110(o, 0);
            func_00230D30(o, st, 1);
            func_002310B8(o, st, 1);
            *cnt = *cnt + 1;
            if (*cnt >= 0x97) {
                func_002113C0(o, 7, 2, 1);
            }
            if (func_00211310(o, 7, 2)) {
                func_001F9D78(o, BtlObjXf_Update(o) + 3);
                *cnt = 0;
            }
            if (func_00241170(o, st)) {
                active = 1;
            }
            break;
        case 6: case 40: case 74:
            func_001F9FB0(o, 0);
            break;
        default:
            break;
        }
    }

    if (doTail && !(func_002411E0(o, st) & 0x400000)) {
        s32 a, b;
        a = BtlObjXf_Update(o) + 7;
        b = BtlObjXf_Update(o) + 0xE;
        func_002177A8(o, a, b, active);
    }
    if (active) {
        f20 = D_00386888;
        func_00215068(o, 1, 0xC, D_0038688C, f20);
        func_00215E88(o, 2, f20);
        func_00216208(o, 0.0f, D_00386890);
    } else {
        f20 = D_00386894;
        func_00215068(o, 5, 0xC, D_00386898, f20);
        func_00215E88(o, 6, f20);
        func_00216208(o, 0.0f, D_0038689C);
    }
    func_00216678(o);
    func_002113C0(o, 9, 0x200, 1);
    func_002113C0(o, 0xD, 8, 1);
    func_002113C0(o, 0xD, 1, 1);
    func_002113C0(o, 0xD, 0x10, 1);
    func_002113C0(o, 9, 0x40000, 1);
    func_002113C0(o, 1, 0x800000, 1);
    if (!(func_002411E0(o, st) & 0x10)) {
        func_00206958(o, 0x8000);
    }
    if (func_00211310(o, 0, 2)) {
        return;
    }
    if (func_00211310(o, 0, 4)) {
        return;
    }
    func_002113C0(o, 0, 2, 1);
}
