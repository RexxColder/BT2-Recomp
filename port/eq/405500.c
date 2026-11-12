#include "m2c_macros.h"

extern void *D_0042BB74 __attribute__((section(".data")));

void func_00405500(s32 arg0) {
    u8 *g;
    u8 *t0;
    u8 *a2;
    u8 *a3;
    s32 k;
    s32 t2;
    s32 t1;
    s32 a1;
    s32 old;
    s32 v;
    s32 x;
    s32 v0;
    s32 nw;

    for (k = 0; k < 7; k++) {
        t2 = 80 * arg0 + 4 * k;
        t1 = t2 + 0x16C;
        g = (u8 *)D_0042BB74;
        t0 = M2C_FIELD(g, u8 **, 4 * arg0 + 0x260);
        a1 = M2C_FIELD(g, s32 *, 4 * arg0 + 0x21C);
        old = M2C_FIELD(g, s32 *, t1 + 0xC);
        a2 = g + 0xC + t2;
        a3 = M2C_FIELD(g, u8 **, 0x18);
        v = 7 * a1 + k;
        x = M2C_FIELD(t0 + 44 * v, s32 *, 0);
        v0 = M2C_FIELD(a3 + 4 * x, s32 *, 4);
        a3 = a3 + (s32)(((u32)v0 >> 2) << 2);
        nw = M2C_FIELD(a3, s32 *, 0x10);
        M2C_FIELD(a2, s32 *, 0x194) = old;
        M2C_FIELD(g, s32 *, t1 + 0xC) = nw;
    }
}
