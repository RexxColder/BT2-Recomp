#include "common.h"

extern f32 D_00386950;
extern f32 D_00386954;

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);
void func_00203C88(u8 *arg0, s64 arg1);
void func_00203888(u8 *a0, s32 a1, s32 a2);
s32 func_00217488(void *arg0);
void func_00210868(s32 arg0, s32 arg1);
s32 BtlAnim_SetBlend(void *arg0, f32 farg0);
f32 BtlUtil_WrapAngle(f32 farg0);

s32 func_002342B8(u8 *obj) {
    s32 ok;
    s32 anim;
    s32 handle;
    s32 keep;
    f32 pos[2];
    f32 base_y;
    f32 hold;
    f32 wrapped;
    f32 t;

    ok = func_00211310((s32)obj, 2, 1) != 0;
    if ((*(s32 *)(obj + 0x8DC) & 1) != 0 && func_00211310((s32)obj, 10, 0x10) == 0) {
        ok = 1;
    }
    if (ok == 0) {
        return -1;
    }

    func_002113C0((s32)obj, 2, 0x100, 1);

    switch (*(s32 *)(obj + 0xAB4)) {
    case 0:
        anim = 0x20;
        break;
    case 1:
        anim = 0x21;
        break;
    case 2:
        anim = 0x97;
        break;
    case 3:
        anim = 0x98;
        break;
    case 4:
        anim = 0x99;
        break;
    case 5:
        anim = func_00217488(obj) + 3;
        break;
    case 6:
        anim = 0x9A;
        break;
    case 7:
        anim = 0xA6;
        break;
    case 8:
        BtlAnim_SetBlend(obj, D_00386950);
        return 6;
    default:
        anim = 0x20;
        break;
    }

    func_002113C0((s32)obj, 1, 0x40000, 1);
    func_002113C0((s32)obj, 1, 0x80000, 1);
    func_002113C0((s32)obj, 6, 0x10, 1);
    handle = func_00210DD8((s32)obj);
    if (func_00203C58(func_00211288(handle), (s32)0x80000000) != 0) {
        func_002113C0((s32)obj, 0, 0x4000, 1);
        func_00203888(obj, 100000, 1);
        handle = func_00210DD8((s32)obj);
        func_00203C88((u8 *)func_00211288(handle), (s32)0x80000000);
    }

    if (*(u8 *)(obj + 0xAB8) != 0) {
        func_002113C0((s32)obj, 6, 1, 1);
        func_00210868((s32)obj, (s32)pos);
        base_y = *(f32 *)(obj + 0xABC);
        keep = *(u8 *)(obj + 0xB54);
        hold = *(f32 *)(obj + 0xAC0);
        if (keep != 0) {
            wrapped = BtlUtil_WrapAngle(pos[1] + base_y);
            *(f32 *)(obj + 0xB68) = hold;
            *(f32 *)(obj + 0xB64) = wrapped;
        } else {
            t = BtlUtil_WrapAngle(pos[1] + base_y);
            *(f32 *)(obj + 0xB64) = BtlUtil_WrapAngle(t + D_00386954);
            *(f32 *)(obj + 0xB68) = -hold;
        }
    }

    return anim;
}
