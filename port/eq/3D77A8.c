#include "m2c_macros.h"

extern void *D_003876A4 __attribute__((section(".data")));

void func_003D77A8(u8 *p) {
    s32 n;
    u8 *g;

    n = M2C_FIELD(p, s32 *, 0x3324);
    for (;;) {
        if (M2C_FIELD(p, u16 *, 16 * n + 0x353C) & 2) {
            g = (u8 *)D_003876A4;
            M2C_FIELD(g, s32 *, 0x18) = M2C_FIELD(g, s32 *, 0x18) & ~0x20;
            M2C_FIELD(p, s32 *, 0x3320) = M2C_FIELD(p, s32 *, 0x3320) + 1;
            if (M2C_FIELD(p, s32 *, 0x3320) < M2C_FIELD(p, s32 *, 0x3318)) {
                M2C_FIELD(p, s32 *, 0x3310) = 0x65;
            }
        }
        n = M2C_FIELD(p, s32 *, 0x3324) + 1;
        M2C_FIELD(p, s32 *, 0x3324) = n;
        if (M2C_FIELD((u8 *)p + 32 * M2C_FIELD(p, u16 *, 16 * n + 0x353E), u16 *, 0x333C) & 1) {
            return;
        }
        if (M2C_FIELD((u8 *)p + 32 * M2C_FIELD(p, u16 *, 16 * n + 0x3540), u16 *, 0x333C) & 1) {
            return;
        }
    }
}
