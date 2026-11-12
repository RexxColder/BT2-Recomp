#include "m2c_macros.h"

extern void *D_0042BB7C __attribute__((section(".data")));

void func_00412970(s32 arg0) {
    u8 *g;
    s32 a1;
    s32 t3;
    s32 t0;
    s32 v0;
    s32 v3;
    u8 *slot;

    g = (u8 *)D_0042BB7C;
    a1 = arg0 << 2;
    t3 = a1 + 0x220;
    t0 = M2C_FIELD(g + 0xC + a1, s32 *, 0x290);
    v3 = 0x40 << (t0 & 31);
    slot = g + 0xC + t3;
    v0 = M2C_FIELD(slot, s32 *, 0);
    if ((v0 & v3) == 0) {
        if (M2C_FIELD(g, s32 *, 0x234) == arg0) {
            if (M2C_FIELD(g + t3, s32 *, 4) == t0) {
                M2C_FIELD(g, s32 *, 0x373C) = 5;
            }
        }
    } else {
        M2C_FIELD(slot, s32 *, 0) = v0 ^ v3;
    }
    M2C_FIELD(slot, s32 *, 0) = M2C_FIELD(slot, s32 *, 0) | (1 << (t0 & 31));
}
