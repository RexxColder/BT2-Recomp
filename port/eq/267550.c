#include "common.h"

extern u8 D_00344750[];
extern u8 D_00344788[];

void func_002673C0(void *arg0);
void func_00266AA0(void *arg0, s32 arg1);
void func_00266950(void *arg0, void *arg1);
s32 func_00266938(void *arg0);

/* 0x00267550: dispatch on arg1 (0..18) for the object at arg0; the per-state record lives at obj+0xDF0. */
void func_00267550(void *arg0, s32 arg1, s32 arg2) {
    u8 *o;
    u8 *s0;
    u8 *a3p;
    u16 cnt;
    f32 f;

    o = (u8 *)arg0;
    if (!(*(s32 *)(o + 0x754) != 0 && *(s32 *)(o + 0x758) != 0 && *(s32 *)(o + 0x75C) != 0)) {
        if (func_00266938(o) == 0) {
            return;
        }
    }
    if ((u32)arg1 >= 0x13) {
        return;
    }

    s0 = o + 0xDF0;
    switch (arg1) {
    case 0:
        func_002673C0(o);
        return;
    case 1:
        func_00266AA0(s0, 1);
        *(s32 *)(s0 + 0x10) = 1;
        return;
    case 2:
        a3p = *(u8 **)(o + 0x1C + 0x764 + 4 * arg2);
        if (a3p == NULL) {
            return;
        }
        *(u8 *)(s0 + 0x30) = 1;
        *(s32 *)(s0 + 0x10) = 2;
        *(u16 *)(s0 + 0x3C) = 0;
        *(u8 **)(s0 + 0x34) = a3p + 0x10;
        *(u16 *)(s0 + 0x3E) = *(u16 *)(a3p + 8);
        *(s32 *)(s0 + 0x38) = arg2;
        *(s32 *)(s0 + 0x40) = 0;
        cnt = *(u16 *)(s0 + 0x3E);
        f = (f32)*(u16 *)(a3p + 0x10 + 4 * cnt - 4);
        *(f32 *)(s0 + 0x44) = f;
        func_00266950(o, s0);
        return;
    case 3:
        *(s32 *)(s0 + 0x24) = 7;
        *(s32 *)(s0 + 0x10) = 3;
        *(u8 **)(s0 + 0x28) = D_00344750;
        *(f32 *)(s0 + 0x18) = (f32)*(s16 *)(D_00344750 + 0x18);
        func_00266950(o, s0);
        return;
    case 5:
        *(s32 *)(s0 + 0x24) = 7;
        *(s32 *)(s0 + 0x10) = 5;
        *(u8 **)(s0 + 0x28) = D_00344750;
        *(f32 *)(s0 + 0x18) = (f32)*(s16 *)(D_00344750 + 0x18);
        func_00266950(o, s0);
        return;
    case 6:
        *(s32 *)(s0 + 0x24) = 10;
        *(s32 *)(s0 + 0x10) = 6;
        *(u8 **)(s0 + 0x28) = D_00344788;
        *(f32 *)(s0 + 0x18) = (f32)*(s16 *)(D_00344788 + 0x24);
        func_00266950(o, s0);
        return;
    case 4:
        return;
    case 7:
        *(s32 *)(s0 + 0x10) = 12;
        *(s32 *)(s0 + 0x14) = 5;
        return;
    default:
        /* cases 8..18: state = index, sub = index - 7 */
        *(s32 *)(s0 + 0x10) = arg1;
        *(s32 *)(s0 + 0x14) = arg1 - 7;
        return;
    }
}
