#include "common.h"

/* GUESS arity: both callees take 4 int arguments (m2c draft); the asm sets t0..t3 too, unchecked. */
s32 func_002D8008(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D5D08(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);

void func_002D7DA0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 sp[14];
    u8 *s0;
    u8 *t2;
    u8 *t3;
    s32 ax;
    s32 ay;
    s32 az;
    s32 bx;
    s32 by;
    s32 cx;
    s32 cy;
    s32 P;
    s32 bP;
    s32 Q;
    s32 R;
    s32 s4;
    s32 s5;
    s32 sgnZ;
    s32 r;
    s32 w;

    s0 = arg1 + 4;
    t2 = arg1 + 0x14;
    t3 = arg1 + 0x24;

    ax = *(s32 *)(s0 + 0);
    ay = *(s32 *)(s0 + 4);
    az = *(s32 *)(s0 + 8);
    bx = *(s32 *)(t2 + 0);
    by = *(s32 *)(t2 + 4);
    cx = *(s32 *)(t3 + 0);
    cy = *(s32 *)(t3 + 4);

    P = ay * az;
    bP = P + (s32)((u32)P >> 31);
    Q = bP >> 1;
    R = (Q + (s32)((u32)bP >> 31)) >> 1;

    sp[6] = 0;
    sp[0] = ax + Q;
    sp[1] = bx + R;
    sp[2] = cx + R;
    sp[3] = ay;
    sp[4] = by;
    sp[5] = cy;

    w = *(s32 *)(arg0 + 8);
    s5 = ay;
    if (w != 0) {
        s5 = w;
    }
    sgnZ = (s32)((u32)az >> 31);
    s4 = (az + sgnZ) >> 1;
    if (*(s32 *)(arg0 + 0xC) != 0) {
        s4 = *(s32 *)(arg0 + 0xC);
    }

    r = func_002D8008(arg2, az + sgnZ, ax + Q, *(s32 *)(arg0 + 8));

    sp[8] = r;
    sp[9] = arg3;
    sp[10] = s5;
    sp[11] = s4;
    sp[12] = ay;
    sp[13] = (az + sgnZ) >> 1;

    if (arg2 == 0x10) {
        func_002D5D08(arg0, arg1, 0xB, sgnZ);
    } else if (arg2 == 0x20) {
        func_002D5D08(arg0, arg1, 0xD, sgnZ);
    }
}
