#include "m2c_macros.h"

extern f32 D_003867B8;
extern f32 D_003867BC;

s32 func_00218838(u8 *obj, s32 arg1);
u8 *BtlChar_GetPos(u8 *obj);
f32 BtlUtil_WrapAngle(f32 a);
s32 func_00217488(u8 *obj);
void func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
void BattleSide_SetChara(u8 *obj, s32 code);
void func_0020FC38(u8 *obj, s32 code);

void func_0022F6B0(u8 *obj, s32 arg1) {
    s32 s2 = 0x114;
    s32 v;
    s32 rot = 0;
    f32 f20;
    u8 *p;
    u8 *q;

    if (func_00218838(obj, arg1) != 0) {
        p = BtlChar_GetPos(obj);
        q = BtlChar_GetPos(obj);
        *(f32 *)(p + 0xB4) = BtlUtil_WrapAngle(*(f32 *)(q + 0xB4) + D_003867B8);
    }
    v = func_00217488(obj) - 0x27;
    if ((u32)v < 6) {
        if (v == 0 || v == 1) {
            s2 = 0x114;
        } else if (v == 2) {
            func_002113C0(obj, 0, 2, 1);
            s2 = 0x115;
        } else if (v == 3) {
            func_002113C0(obj, 0, 2, 1);
            p = BtlChar_GetPos(obj);
            *(s32 *)(p + 0xC0) = 0;
            s2 = 0x116;
            rot = 1;
        } else if (v == 4) {
            func_002113C0(obj, 0, 2, 1);
            s2 = 0x117;
        } else {
            func_002113C0(obj, 0, 2, 1);
            p = BtlChar_GetPos(obj);
            *(s32 *)(p + 0xC0) = 0;
            s2 = 0x118;
            rot = 1;
        }
    }
    if (rot) {
        f20 = D_003867BC;
        p = BtlChar_GetPos(obj);
        q = BtlChar_GetPos(obj);
        *(f32 *)(p + 0xB4) = BtlUtil_WrapAngle(*(f32 *)(q + 0xB4) + f20);
        p = BtlChar_GetPos(obj);
        q = BtlChar_GetPos(obj);
        *(f32 *)(p + 0x14) = BtlUtil_WrapAngle(*(f32 *)(q + 0x14) + f20);
    }
    BattleSide_SetChara(obj, s2);
    func_0020FC38(obj, 0x21);
}
