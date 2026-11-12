#include "common.h"
void bt2_fightlog_note(const char *fmt, ...);

extern s32 func_00217488(u8 *obj);
extern void func_002113C0(u8 *obj, s32 a, s32 b, s32 c);
extern void func_00212890(s32 a);
extern u8 *BtlMember_GetActiveGauge(u8 *obj);
extern s32 func_00212320(u8 *obj);
extern s32 func_002411E0(u8 *obj, s32 a);
extern void func_00203310(u8 *obj, s32 a, s32 b);
extern s32 func_0023C710(u8 *obj);
extern s32 func_00210DD8(u8 *obj);
extern s32 func_00211288(s32 a);
extern s32 func_00203C58(s32 a, s64 b);
extern void func_00203C88(s32 a, s64 b);
extern void func_00203888(u8 *obj, s32 a, s32 b);
extern u8 *BtlChar_GetPos(u8 *obj);
extern f32 BtlUtil_WrapAngle(f32 a);
extern void func_00215E30(u8 *obj, f32 a, f32 b);
extern f32 D_003869CC;
extern f32 D_003869D0;

s32 func_00235F38(u8 *obj) {
    s32 state;
    s32 ret;
    f32 angle;
    f32 side;
    f32 turn;

    if ((*(s32 *)(obj + 0x8DC) & 1) == 0) {
        return -1;
    }
    state = func_00217488(obj);
    if (state < 0xC1) {
        return -1;
    }
    if (state < 0xC4) {
        func_002113C0(obj, 5, 0x100, 1);
        func_002113C0(obj, 2, 0x100, 1);
        func_00212890(0x5A);
        if (*(s32 *)(obj + 0x8DC) & 2) {
            func_002113C0(obj, 0xC, 0x20000, 1);
            *(u8 *)(BtlMember_GetActiveGauge(obj) + 0x2C) = 1;
            bt2_fightlog_note("B3 MARCA-2C chr %08X estado %X 8DC %08X", (s32)obj, state, *(s32 *)(obj + 0x8DC)); /* TEMP */
        }
        if (func_002411E0(obj, func_00212320(obj)) & 0x400) {
            func_00203310(obj, *(s32 *)BtlMember_GetActiveGauge(obj) - 1, 0x5B);
            func_002113C0(obj, 6, 0x10, 1);
        }
        if (func_002411E0(obj, func_00212320(obj)) & 0x200000) {
            func_002113C0(obj, 1, 0x40000, 1);
            func_002113C0(obj, 1, 0x80000, 1);
            func_002113C0(obj, 2, 0x1000, 1);
            return 0x21;
        }
        return func_0023C710(obj);
    }
    if (state >= 0xC7) {
        return -1;
    }
    func_002113C0(obj, 2, 0x100, 1);
    ret = 0x20;
    if (*(u8 *)(obj + 0xA85) != 0 || (*(s32 *)(obj + 0x8DC) & 2)) {
        func_002113C0(obj, 0, 2, 1);
        return 6;
    }
    func_002113C0(obj, 6, 0x10, 1);
    func_002113C0(obj, 1, 0x40000, 1);
    func_002113C0(obj, 1, 0x80000, 1);
    switch (*(u32 *)(obj + 0xA78)) {
    case 0: ret = 0x20; break;
    case 1: ret = 0x21; break;
    case 2: ret = 0x97; break;
    case 3: ret = 0x98; break;
    case 4: ret = 0x99; break;
    case 5: ret = func_00217488(obj) + 3; break;
    case 6: ret = 0x9A; break;
    case 7: ret = 0xA6; break;
    default: break;
    }
    if (func_00203C58(func_00211288(func_00210DD8(obj)), (s64)0x8000 << 16)) {
        func_002113C0(obj, 0, 0x4000, 1);
        func_00203888(obj, 0x186A0, 1);
        func_00203C88(func_00211288(func_00210DD8(obj)), (s64)0x8000 << 16);
    }
    if (*(u8 *)(obj + 0xA84) != 0) {
        func_002113C0(obj, 6, 1, 1);
        side = *(f32 *)(obj + 0xA88);
        turn = *(f32 *)(obj + 0xA8C);
        angle = *(f32 *)(BtlChar_GetPos(obj) + 0x14);
        if (*(u8 *)(obj + 0xB54) != 0) {
            *(f32 *)(obj + 0xB64) = BtlUtil_WrapAngle(angle + side);
            *(f32 *)(obj + 0xB68) = turn;
        } else {
            f32 a = BtlUtil_WrapAngle(angle + side);
            *(f32 *)(obj + 0xB64) = BtlUtil_WrapAngle(a + D_003869CC);
            *(f32 *)(obj + 0xB68) = -turn;
        }
    } else {
        if (*(u8 *)(obj + 0xB54) == 0) {
            return ret;
        }
        angle = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(obj) + 0xB4) + D_003869D0);
        func_00215E30(obj, angle, *(f32 *)(BtlChar_GetPos(obj) + 0xB0));
    }
    if (*(u8 *)(obj + 0xB54) != 0) {
        func_002113C0(obj, 2, 0x1000, 1);
    }
    return ret;
}
