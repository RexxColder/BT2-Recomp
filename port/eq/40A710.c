#include "m2c_macros.h"

extern void *D_0042BB78 __attribute__((section(".data")));

void func_0040A710(s32 arg0) {
    u8 *g;
    u8 *a3;
    u8 *t1;
    s32 k;
    s32 t4;
    s32 t3;
    s32 w;
    s32 t0;
    s32 x0;
    s32 v;
    s32 x;
    s32 v0;
    s32 nw;

    for (k = 0; k < 7; k++) {
        t4 = 80 * arg0 + 4 * k;
        t3 = t4 + 0x19C;
        g = (u8 *)D_0042BB78;
        t1 = M2C_FIELD(g, u8 **, 4 * arg0 + 0x360);
        w = M2C_FIELD(g, s32 *, 4 * arg0 + 0x2DC);
        t0 = M2C_FIELD(g, s32 *, t3 + 0xC);
        x0 = M2C_FIELD(g, s32 *, 0x26C + 4 * (5 * arg0 + w));
        v = 7 * x0 + k;
        x = M2C_FIELD(t1 + 44 * v, s32 *, 0);
        a3 = M2C_FIELD(g, u8 **, 0x18);
        v0 = M2C_FIELD(a3 + 4 * x, s32 *, 4);
        a3 = a3 + (s32)(((u32)v0 >> 2) << 2);
        nw = M2C_FIELD(a3, s32 *, 0x10);
        M2C_FIELD(g, s32 *, t4 + 0x1D0) = t0;
        M2C_FIELD(g, s32 *, t3 + 0xC) = nw;
    }
}
