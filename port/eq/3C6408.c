#include "m2c_macros.h"

extern void *D_00423114 __attribute__((section(".data")));

void func_003C6408(s32 arg0) {
    s32 a;
    s32 k;
    u8 *g;
    u8 *t1;
    u8 *a3;
    s32 a2;
    s32 old;
    s32 v;
    s32 x;
    s32 v0;
    s32 nw;

    a = arg0 << 2;
    for (k = 0; k < 7; k++) {
        g = (u8 *)D_00423114;
        t1 = M2C_FIELD(g, u8 **, a + 0x1CC);
        a2 = M2C_FIELD(g, s32 *, a + 0x198);
        old = M2C_FIELD(g, s32 *, 4 * k + 0x144);
        a3 = M2C_FIELD(g, u8 **, 0x10);
        v = 7 * a2 + k;
        x = M2C_FIELD(t1 + 44 * v, s32 *, 0);
        v0 = M2C_FIELD(a3 + 4 * x, s32 *, 4);
        a3 = a3 + (s32)(((u32)v0 >> 2) << 2);
        nw = M2C_FIELD(a3, s32 *, 0x10);
        M2C_FIELD(g, s32 *, 4 * k + 0x16C) = old;
        M2C_FIELD(g, s32 *, 4 * k + 0x144) = nw;
    }
}
