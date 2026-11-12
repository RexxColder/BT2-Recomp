#include "common.h"

/* 0x00233200: per-frame state handler (states 0x11C-0x182, three variants of 4 sub-states, and 0x182). */
s32 BtlObjXf_Update(u8 *obj);
s32 BtlPad_Test4C(u8 *obj, s32 btn);
s32 BtlPad_GetMask(u8 *obj, s32 arg);
void BtlAnim_SetBlend(u8 *obj, f32 blend);
void BtlChar_SetVibration(u8 *obj, f32 a, f32 b);
s32 *BtlMember_GetActiveGauge(u8 *obj);
s32 func_001F9D78(u8 *obj, s32 state);
s32 func_001F9FB0(u8 *obj, s32 arg);
s32 func_001FA0A0(u8 *obj, s32 state, s32 arg);
s32 func_001FA110(u8 *obj, s32 arg);
s32 func_001FA2E0(u8 *obj);
void func_001FCD80(u8 *obj);
void func_00206958(u8 *obj, s32 flags);
s32 func_00203310(u8 *obj, s32 a, s32 b);
s32 func_00211310(u8 *obj, s32 a, s32 b);
s32 func_002113C0(u8 *obj, s32 a, s32 b, s32 c);
s32 func_00212320(u8 *obj);
s32 func_00215068(u8 *obj, s32 a, s32 b, f32 f0, f32 f1);
s32 func_00215E88(u8 *obj, s32 a, f32 f0);
s32 func_00216208(u8 *obj, f32 f0, f32 f1);
s32 func_00216678(u8 *obj);
void func_002171C0(u8 *obj, f32 a, f32 b);
void func_002177A8(u8 *obj, s32 a, s32 b, s32 c);
void func_00230BB0(u8 *obj, s32 a);
void func_00230C48(u8 *obj);
void func_00230C60(u8 *obj, s32 a);
void func_00230D30(u8 *obj, s32 a, s32 b);
void func_002310B8(u8 *obj, s32 a, s32 b);
f32 func_00241218(u8 *obj, s32 a);
s32 func_002411E0(u8 *obj, s32 a);
s32 func_00241778(u8 *obj, s32 a);

extern f32 D_003868FC;
extern f32 D_00386900;
extern f32 D_00386904;
extern f32 D_00386908;
extern f32 D_0038690C;
extern f32 D_00386910;
extern f32 D_00386914;
extern f32 D_00386918;
extern f32 D_0038691C;
extern f32 D_00386920;
extern f32 D_00386924;

s32 func_00233200(u8 *obj) {
    s32 *counter = (s32 *)(obj + 0x8C0);
    s32 *counter2 = (s32 *)(obj + 0x8C4);
    s32 flag_a = 0;
    s32 flag_b = 0;
    s32 flag_c = 1;
    s32 member;
    s32 r;
    s32 v;

    member = func_00212320(obj);
    switch (BtlObjXf_Update(obj)) {
    case 0x11C:
    case 0x13E:
    case 0x160:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        if (func_001FA2E0(obj) != 0) {
            func_00230BB0(obj, member);
        }
        func_00230C60(obj, 0);
        flag_a = 1;
        func_002113C0(obj, 9, 4, 1);
        break;
    case 0x11D:
    case 0x13F:
    case 0x161:
        func_001FA110(obj, 0);
        BtlChar_SetVibration(obj, D_003868FC, D_00386900);
        *counter = *counter + 1;
        if (*counter >= 0x97) {
            func_002113C0(obj, 7, 1, 1);
        }
        if (func_00211310(obj, 7, 1) != 0) {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 1);
            *counter = 0;
        }
        func_00230C60(obj, 0);
        flag_a = 1;
        func_002113C0(obj, 9, 4, 1);
        break;
    case 0x11E:
    case 0x140:
    case 0x162:
        if (func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0) != 0) {
            if (func_00203310(obj, func_00241778(obj, member), 0x2F) != 0) {
                func_002113C0(obj, 6, 4, 1);
            }
            *counter2 = *counter2 + 1;
        }
        if (func_001FA2E0(obj) != 0) {
            func_001FCD80(obj);
        }
        flag_b = 1;
        func_00230D30(obj, member, 0);
        func_002310B8(obj, member, 0);
        flag_a = 1;
        *counter = *counter + 1;
        break;
    case 0x11F:
    case 0x141:
    case 0x163: {
        s32 done = 0;
        func_001FA110(obj, 0);
        func_00230D30(obj, member, 1);
        func_002310B8(obj, member, 1);
        *counter = *counter + 1;
        flag_b = 1;
        flag_a = 1;
        if (*counter >= (s32)(func_00241218(obj, member) * 30.0f) - 1) {
            done = 1;
        } else if (*BtlMember_GetActiveGauge(obj) == flag_b || *counter2 == 10) {
            done = 1;
        } else {
            if (BtlPad_Test4C(obj, 1) != 0 && *counter >= 16) {
                func_001F9D78(obj, BtlObjXf_Update(obj) - 1);
                BtlAnim_SetBlend(obj, D_00386904);
                *counter = 0;
            }
            if (BtlPad_Test4C(obj, 3) != 0) {
                done = 1;
            } else if (BtlPad_Test4C(obj, 0) != 0) {
                done = 1;
            } else if (BtlPad_Test4C(obj, 2) != 0) {
                done = 1;
            }
        }
        if (done != 0) {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 3);
            *counter = 0;
        }
        break;
    }
    case 0x122:
    case 0x144:
    case 0x166:
        func_001F9FB0(obj, 0);
        break;
    case 0x182:
        func_001FA0A0(obj, 0x160, 0);
        if (func_001FA2E0(obj) != 0) {
            func_00230C48(obj);
        }
        func_00230C60(obj, 0);
        flag_c = 0;
        func_002113C0(obj, 9, 4, 1);
        break;
    default:
        break;
    }

    if (flag_c != 0) {
        s32 a;
        s32 b;
        func_002171C0(obj, D_00386908, D_0038690C);
        if ((func_002411E0(obj, member) & 0x400000) == 0) {
            a = BtlObjXf_Update(obj) + 7;
            b = BtlObjXf_Update(obj) + 14;
            func_002177A8(obj, a, b, flag_a);
        }
        func_00215068(obj, 1, 12, D_00386910, D_00386914);
    } else {
        func_00215068(obj, 5, 12, D_00386918, D_0038691C);
    }
    func_00215E88(obj, 6, D_00386920);
    func_00216208(obj, 0.0f, D_00386924);
    func_00216678(obj);
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 13, 8, 1);
    func_002113C0(obj, 13, 1, 1);
    func_002113C0(obj, 13, 0x10, 1);
    func_002113C0(obj, 9, 0x40000, 1);
    func_002113C0(obj, 1, 0x800000, 1);
    if ((func_002411E0(obj, member) & 0x10) == 0) {
        func_00206958(obj, 0x8000);
    }
    r = func_00211310(obj, 0, 2);
    if (r == 0) {
        r = func_00211310(obj, 0, 4);
        if (r == 0) {
            r = func_002113C0(obj, 0, 2, 1);
        }
    }
    if (flag_b != 0) {
        s32 *gauge = BtlMember_GetActiveGauge(obj);
        r = (s32)gauge;
        if (*gauge >= 2) {
            v = BtlPad_GetMask(obj, 1);
            if (v == 0x2000) {
                return func_002113C0(obj, 15, 1, 1);
            } else if (v >= 0x2001) {
                r = 0x8000;
                if (v == 0x4000) {
                    return func_002113C0(obj, 15, 2, 1);
                } else if (v == 0x8000) {
                    return func_002113C0(obj, 15, 8, 1);
                }
            } else {
                r = 0x1000;
                if (v == 0x1000) {
                    return func_002113C0(obj, 15, 4, 1);
                }
            }
        }
    }
    return r;
}
