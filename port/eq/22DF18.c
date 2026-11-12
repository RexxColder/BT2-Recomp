#include "common.h"

extern s32 func_00203C58(u8 *obj, s64 a);
extern s32 func_00211310(u8 *obj, s32 a, s64 b);
extern void func_002113C0(u8 *obj, s32 a, s32 b, s32 c);
extern void func_00212890(s32 a);
extern s32 func_00217490(u8 *obj);
extern s32 func_00217488(u8 *obj);
extern void BattleSide_SetChara(u8 *obj, s32 a);
extern void func_00203888(u8 *obj, s32 a, s32 b);
extern void BtlOpp_GetDelta(u8 *obj, f32 *out);
extern f32 func_0029DFD0(f32 *v);
extern void func_00312680(f32 scale, f32 *out, f32 *in);
extern f32 atan2f(f32 y, f32 x);
extern f32 Mathf_Asin(f32 x);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void sceVu0Normalize(f32 *out, f32 *in);
extern u8 *BtlChar_GetPos(u8 *obj);
extern void func_00206958(u8 *obj, s64 a);
extern void func_0020FC38(u8 *obj, s32 a);
extern void func_00210868(u8 *obj, f32 *out);
extern f32 BtlUtil_WrapAngle(f32 a);
extern void func_00212DD8(u8 *obj, s32 a);
extern f32 D_003866EC;
extern f32 D_003866F0;

void func_0022DF18(u8 *obj) {
    s32 chara = 0x4000;
    f32 dir[4];
    f32 delta[4];
    f32 info[8];
    f32 len;
    f32 yaw;
    f32 pitch;
    f32 *pos;
    s32 state;

    if (func_00203C58(obj, 0x4000)) {
        chara = 0;
    }
    if (func_00211310(obj, 4, (s64)(s32)0xE0000000)) {
        *(s32 *)(obj + 0x8DC) |= 2;
        func_002113C0(obj, 1, 0x1000000, 1);
        func_00212890(0x3C);
    } else {
        s32 st = func_00217490(obj);
        if (st < 0xF && st >= 0xD) {
            *(s32 *)(obj + 0x8DC) |= 2;
        } else {
            BattleSide_SetChara(obj, 0x10C);
            func_00203888(obj, chara, 0);
        }
    }
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = 0.0f;
    BtlOpp_GetDelta(obj, delta);
    *(f32 *)(obj + 0x8D0) = __builtin_sqrtf(delta[0] * delta[0] + delta[2] * delta[2]);
    len = func_0029DFD0(delta);
    if (D_003866EC < len) {
        func_00312680(1.0f / len, delta, delta);
        if (delta[0] < -1.0f) {
            delta[0] = -1.0f;
        }
        if (delta[1] < -1.0f) {
            delta[1] = -1.0f;
        }
        if (delta[2] < -1.0f) {
            delta[2] = -1.0f;
        }
        if (delta[0] > 1.0f) {
            delta[0] = 1.0f;
        }
        if (delta[1] > 1.0f) {
            delta[1] = 1.0f;
        }
        if (delta[2] > 1.0f) {
            delta[2] = 1.0f;
        }
    }
    yaw = -atan2f(delta[0], delta[2]);
    pitch = Mathf_Asin(delta[1]);
    state = func_00217488(obj);
    if (state == 0x1D) {
        dir[0] = 1.0f;
        *(s32 *)(obj + 0x8DC) |= 1;
    } else if (state == 0x1C) {
        dir[0] = -1.0f;
        *(s32 *)(obj + 0x8DC) |= 1;
    } else if (state == 0x1E) {
        dir[1] = pitch;
        dir[2] = __builtin_sqrtf(1.0f - pitch * pitch);
    } else if (state == 0x1F) {
        dir[1] = pitch;
        dir[2] = -1.0f;
    }
    sceVu0Normalize(dir, dir);
    pos = (f32 *)BtlChar_GetPos(obj);
    pos[8] = dir[0] * cosf(yaw) - dir[2] * sinf(yaw);
    pos = (f32 *)BtlChar_GetPos(obj);
    pos[9] = dir[1];
    pos = (f32 *)BtlChar_GetPos(obj);
    pos[10] = dir[0] * sinf(yaw) + dir[2] * cosf(yaw);
    *(s32 *)(obj + 0x8C0) = 8;
    func_00206958(obj, 0x2000);
    func_002113C0(obj, 0, 2, 1);
    func_0020FC38(obj, 0x20);
    if ((*(s32 *)(obj + 0x8DC) & 1) && func_00211310(obj, 1, 1)) {
        func_00210868(obj, info);
        if (D_003866F0 < __builtin_fabsf(BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(obj) + 0xB4) - info[1]))) {
            func_00212DD8(obj, 0x1D);
        }
    }
}
