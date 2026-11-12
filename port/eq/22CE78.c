#include "common.h"

extern void BtlOpp_GetDelta(s32 obj, f32 *out);
extern f32 func_0029DFD0(f32 *v);
extern void func_00312680(f32 *dst, f32 *src, f32 scale);
extern f32 atan2f(f32 y, f32 x);
extern s32 func_00217488(s32 obj);
extern f32 func_00217330(s32 obj);
extern void func_002113C0(s32 obj, s32 a1, s32 a2, s32 a3);
extern s32 func_00211310(s32 obj, s32 a1, s32 a2);
extern void BattleSide_SetChara(s32 obj, s32 chara);
extern u8 *BtlChar_GetPos(s32 obj);
extern void sceVu0Normalize(f32 *dst, f32 *src);
extern f32 cosf(f32 x);
extern f32 sinf(f32 x);
extern void func_0020FC38(s32 obj, s32 a1);
extern void func_002100C0(s32 obj, s32 a1);
extern void func_00212DD8(s32 obj, s32 a1);
extern f32 D_00386644;

void func_0022CE78(s32 obj) {
    f32 dir[4];
    f32 delta[4];
    s32 chara = 0;
    s32 s3 = -1;
    s32 s4 = -1;
    s32 s5 = -1;
    f32 ang;
    f32 len;
    f32 x, y, z;
    u8 *pos;

    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = 0.0f;
    BtlOpp_GetDelta(obj, delta);
    len = func_0029DFD0(delta);
    if (D_00386644 < len) {
        func_00312680(delta, delta, 1.0f / len);
        if (delta[0] < -1.0f) {
            delta[0] = -1.0f;
        }
        if (delta[1] < -1.0f) {
            delta[1] = -1.0f;
        }
        if (delta[2] < -1.0f) {
            delta[2] = -1.0f;
        }
        if (1.0f < delta[0]) {
            delta[0] = 1.0f;
        }
        if (1.0f < delta[1]) {
            delta[1] = 1.0f;
        }
        if (1.0f < delta[2]) {
            delta[2] = 1.0f;
        }
    }
    ang = -atan2f(delta[0], delta[2]);

    switch (func_00217488(obj)) {
    case 21:
        if (func_00217330(obj) < 5.0f) {
            func_002113C0(obj, 0, 2, 0);
        }
        chara = 0x35;
        if (func_00211310(obj, 0, 0x102) == 0) {
            chara = 0x29;
        }
        s5 = 1;
        s3 = 8;
        dir[0] = -1.0f;
        break;
    case 22:
        if (func_00217330(obj) < 5.0f) {
            func_002113C0(obj, 0, 2, 0);
        }
        chara = 0x36;
        if (func_00211310(obj, 0, 0x102) == 0) {
            chara = 0x2A;
        }
        s5 = 1;
        s3 = 8;
        dir[0] = 1.0f;
        break;
    case 23:
        break;
    case 24:
        if (func_00217330(obj) < 5.0f) {
            func_002113C0(obj, 0, 2, 0);
        }
        chara = 0x34;
        if (func_00211310(obj, 0, 0x102) == 0) {
            chara = 0x28;
        }
        s4 = 0x1F;
        s3 = 9;
        dir[2] = -1.0f;
        break;
    case 25:
        chara = 0x34;
        s4 = 0x1F;
        dir[1] = -2.0f;
        s3 = 9;
        dir[2] = -1.0f;
        break;
    case 26:
        chara = 0x34;
        s4 = 0x1F;
        dir[1] = 2.0f;
        s3 = 9;
        dir[2] = -1.0f;
        break;
    default:
        break;
    }

    BattleSide_SetChara(obj, chara);
    sceVu0Normalize(dir, dir);
    pos = BtlChar_GetPos(obj);
    x = dir[0] * cosf(ang);
    y = dir[2] * sinf(ang);
    *(f32 *)(pos + 0x20) = x - y;
    pos = BtlChar_GetPos(obj);
    *(f32 *)(pos + 0x24) = dir[1];
    pos = BtlChar_GetPos(obj);
    z = dir[0] * sinf(ang);
    y = dir[2] * cosf(ang);
    *(f32 *)(pos + 0x28) = z + y;
    if (s4 >= 0) {
        func_0020FC38(obj, s4);
    }
    if (s5 >= 0) {
        func_002100C0(obj, s5);
    }
    if (s3 >= 0) {
        func_00212DD8(obj, s3);
    }
}
