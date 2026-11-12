#include "m2c_macros.h"

extern void *D_0042A570 __attribute__((section(".data")));

void func_003F0748(s32 arg0) {
    u8 *g;
    s32 k;
    s32 a1;
    u8 *t0;
    u8 *a2;
    s32 t3;
    s32 a3off;
    s32 old;
    s32 v;
    s32 x;
    s32 v0;
    s32 nw;

    g = (u8 *)D_0042A570;
    for (k = 0; k < 7; k++) {
        t3 = 80 * arg0 + 4 * k;
        a1 = M2C_FIELD(g, s32 *, 4 * arg0 + 0x224);
        t0 = M2C_FIELD(g, u8 **, 4 * arg0 + 0x258);
        a2 = M2C_FIELD(g, u8 **, 0x18);
        a3off = t3 + 0x17C;
        old = M2C_FIELD(g, s32 *, a3off);
        M2C_FIELD(g, s32 *, t3 + 0x1A4) = old;
        v = 7 * a1 + k;
        x = M2C_FIELD(t0 + 44 * v, s32 *, 0);
        v0 = M2C_FIELD(a2 + 4 * x, s32 *, 4);
        a2 = a2 + (s32)(((u32)v0 >> 2) << 2);
        nw = M2C_FIELD(a2, s32 *, 0x10);
        M2C_FIELD(g, s32 *, a3off) = nw;
    }
}
