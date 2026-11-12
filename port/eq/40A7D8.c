#include "m2c_macros.h"

extern void *D_0042BB78 __attribute__((section(".data")));

void func_0040A7D8(s32 arg0) {
    u8 *g;
    s32 a2s;
    s32 k;
    s32 j;
    s32 t1;
    s32 x;
    u8 *a0;
    s32 w;

    a2s = (arg0 != 0) ? 0x13 : 0xE;
    g = (u8 *)D_0042BB78;
    for (k = 0; k < 5; k++) {
        M2C_FIELD(g, s32 *, 4 * a2s + 0x11C - 4 * k) = 0;
    }
    if (M2C_FIELD(g, s32 *, 4 * arg0 + 0x2DC) <= 0) {
        return;
    }
    j = 0;
    do {
        t1 = 4 * a2s + 0x110 - 4 * j;
        x = M2C_FIELD(g, s32 *, 4 * (5 * arg0 + j) + 0x2E4);
        a0 = M2C_FIELD(g, u8 **, 0x18);
        w = M2C_FIELD(a0 + 4 * x, s32 *, 4);
        a0 = a0 + (s32)(((u32)w >> 2) << 2);
        M2C_FIELD(g, s32 *, t1 + 0xC) = M2C_FIELD(a0, s32 *, 0x10);
        j += 1;
    } while (j < M2C_FIELD(g, s32 *, 4 * arg0 + 0x2DC));
}
