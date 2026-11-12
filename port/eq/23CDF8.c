#include "common.h"
extern f32 D_00386C3C;
extern f32 D_00386C40;
extern f32 D_00386C44;
extern f32 D_00386C48;
extern f32 BtlUtil_WrapAngle(f32 a);
extern s32 BtlMember_IsHealthEmpty_2127F8();
extern s32 func_002113C0();
extern s32 func_00203888();
extern s32 func_00203C58();
extern s32 func_00203C88();
extern s32 func_00210DD8();
extern s32 func_00211288();

s32 func_0023CDF8(u8 *p, s32 n) {
    s32 ret = -1;
    u8 *q;
    f32 f;
    if ((u32)n < 2) return -1;
    if (n == 2) {
        if (!BtlMember_IsHealthEmpty_2127F8(p)) return -1;
    }
    q = p + n + 0xB98;
    if (*(s8 *)q < 100) *q = *q + 1;
    if (n >= 9 && (n < 13 || (n < 35 && n >= 33))) {
        if (*(s8 *)q >= 2) {
            func_002113C0(p, 6, 1, 1);
            n = 15;
            if (*(u8 *)(p + 0xB54)) f = *(f32 *)(p + 0xB5C);
            else f = BtlUtil_WrapAngle(*(f32 *)(p + 0xB5C) + D_00386C3C);
            *(s32 *)(p + 0xB68) = 0;
            *(f32 *)(p + 0xB64) = f;
            *(f32 *)(p + 0xB60) = D_00386C40;
        }
    }
    if (func_00203C58(func_00211288(func_00210DD8(p)), 0x80000000u)) {
        switch (n) {
        case 10: case 11: case 14: case 15: case 16: case 17: case 36: case 38: case 39:
            func_002113C0(p, 0, 0x4000, 1);
            func_00203888(p, 100000, 1);
            func_00203C88(func_00211288(func_00210DD8(p)), 0x80000000u);
            break;
        default: break;
        }
    }
    if (BtlMember_IsHealthEmpty_2127F8(p) && n >= 2 && (n < 10 || (n < 24 && n >= 21))) {
        func_002113C0(p, 6, 1, 1);
        n = 14;
        if (*(u8 *)(p + 0xB54)) f = *(f32 *)(p + 0xB5C);
        else f = BtlUtil_WrapAngle(*(f32 *)(p + 0xB5C) + D_00386C44);
        *(s32 *)(p + 0xB68) = 0;
        *(f32 *)(p + 0xB64) = f;
        *(f32 *)(p + 0xB60) = D_00386C48;
    }
    switch (n) {
    case 3: ret = 0x8E; break;
    case 4: ret = 0x8F; break;
    case 5: ret = 0x90; break;
    case 6: ret = 0x91; break;
    case 7: ret = 0x92; break;
    case 8: ret = 0x93; break;
    case 9: ret = 0x94; break;
    case 10: ret = 0x95; break;
    case 11: ret = 0x96; break;
    case 12: case 37: ret = 0x9C; break;
    case 13: ret = 0xA5; break;
    case 14: ret = 0x97; break;
    case 15: ret = 0x98; break;
    case 16: ret = 0x99; break;
    case 17: ret = 0x9A; break;
    case 18: ret = 0x80; break;
    case 20: ret = 0x84; break;
    case 21: ret = 0x9F; if (*(s32 *)(p + 0xB74) < 15) *(s32 *)(p + 0xB74) = 15; break;
    case 22: ret = 0x9F; if (*(s32 *)(p + 0xB74) < 30) *(s32 *)(p + 0xB74) = 30; break;
    case 23: ret = 0x9F; if (*(s32 *)(p + 0xB74) < 45) *(s32 *)(p + 0xB74) = 45; break;
    case 24: ret = 0xAA; if (*(s32 *)(p + 0xB74) < 15) *(s32 *)(p + 0xB74) = 15; break;
    case 25: ret = 0xAA; if (*(s32 *)(p + 0xB74) < 30) *(s32 *)(p + 0xB74) = 30; break;
    case 26: ret = 0xAA; if (*(s32 *)(p + 0xB74) < 45) *(s32 *)(p + 0xB74) = 45; break;
    case 27: ret = *(s32 *)(p + 0xAB0) + 0xCE; break;
    case 28: ret = *(s32 *)(p + 0xAB0) + 0xD1; break;
    case 29: ret = 0xA6; break;
    case 30: ret = 0xA7; break;
    case 31: ret = 0xA8; break;
    case 32: ret = *(s32 *)(p + 0xA70) + 0xC2; break;
    case 33: ret = 0xA2; break;
    case 34: ret = 0xA3; break;
    case 35: ret = 0x86; break;
    case 36: ret = 0xA4; break;
    case 38: ret = 0xAB; break;
    case 39: ret = *(s32 *)(p + 0xB88) + 0xD4; break;
    default: break;
    }
    func_002113C0(p, 9, 0x4000000, 1);
    return ret;
}
