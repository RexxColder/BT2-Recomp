#include "common.h"

extern f32 D_00385BA8;
extern f32 D_00385BAC;
extern f32 D_00385BB0;
extern f32 D_00385BB4;
extern f32 D_00385BB8;
extern f32 D_00385BBC;
extern f32 D_00385BC0;
extern f32 D_00385BC4;
extern f32 D_00385BC8;
extern f32 D_00385BCC;
extern u8 D_002C3630[] __attribute__((section(".data")));

f32 BtlCharApi_GetHeight(s32 arg0);
void func_00217CB8(s32 arg0);
s32 func_00217488(void *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_0020FC38(u8 *a0, s32 a1);
s32 func_0023F2D8(u8 *arg0);
void func_00212DD8(u8 *arg0, s32 arg1);
void *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 func_001FA340(u8 *a0);
s32 func_001FC3B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);

s32 func_00219908(u8 *obj) {
    f32 side = 0.0f;
    f32 lat = 0.0f;
    f32 base_h;
    f32 vert;
    f32 yaw;
    f32 h;
    s32 anim = 0;
    s32 kind;
    u8 *pos;
    s32 view;

    base_h = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534)) * D_00385BA8;
    yaw = -base_h;
    vert = yaw * D_00385BAC;

    kind = func_00217488(obj);
    switch (kind) {
    case 80:
        side = D_00385BB0;
        anim = 98;
        break;
    case 81:
        side = D_00385BB4;
        anim = 101;
        break;
    case 82:
        lat = D_00385BB8;
        anim = 92;
        break;
    case 83:
        lat = D_00385BBC;
        anim = 95;
        break;
    case 84:
        vert = yaw * D_00385BC0;
        anim = 86;
        break;
    case 85:
        vert = yaw * D_00385BC4;
        anim = 89;
        break;
    default:
        break;
    }

    BattleSide_SetChara(obj, anim);
    func_00217CB8((s32)obj);
    if (func_00211310((s32)obj, 0, 1) != 0) {
        func_00215068(obj, 1, 12, D_00385BC8, 1.0f);
    }
    func_0020FC38(obj, 46);
    func_0020FC38(obj, 23);
    func_0020FC38(obj, 38);

    view = func_0023F2D8(obj);
    func_00212DD8(obj, view);

    pos = (u8 *)BtlChar_GetPos((s32)obj);
    yaw = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) + D_00385BCC);
    yaw = BtlUtil_WrapAngle(yaw - side);

    h = func_001FA340(obj);
    return func_001FC3B0(obj, (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630,
                         (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630, 17,
                         17, 17, 17, (s32)(h * 0.5f + 15.0f), 199,
                         yaw, side, 0.0f - lat, lat, base_h - vert, vert);
}
