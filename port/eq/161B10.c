#include "common.h"

/* GUESS arity: func_0019F8D0 gets a0 = buf, a1/a2 = 64-bit words, a3 = pass-through; ctx.h says 2 */
void func_0019F8D0(s32 *arg0, s64 arg1, s64 arg2, s32 arg3);
s32 func_0020B3D0(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
extern s64 D_0036E420[] __attribute__((section(".data")));

void func_00161B10(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *obj;
    s32 *p;
    s64 buf[4];

    obj = *(u8 **)(arg0 + 0x38);
    p = *(s32 **)(obj + 0x70);
    if (EftShot_TestBits(func_0020B3D0(p[0]), 0x40) != 0) {
        buf[0] = D_0036E420[0];
        buf[1] = D_0036E420[1];
        buf[2] = D_0036E420[2];
        buf[3] = D_0036E420[3];
        func_0019F8D0((s32 *)buf, D_0036E420[2], D_0036E420[3], arg3);
    }
}
