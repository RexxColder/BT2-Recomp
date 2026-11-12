#include "m2c_macros.h"

extern void *D_003876A4 __attribute__((section(".data")));
extern s32 D_00387F2C __attribute__((section(".data")));
extern void *D_0042A574 __attribute__((section(".data")));

s32 func_003F4298(s32 arg0) {
    u8 *g1;
    u8 *p2;
    s32 t0;
    s32 flag;
    s32 addr;

    g1 = (u8 *)D_003876A4;
    t0 = arg0 * 7 * 8;
    flag = M2C_FIELD((u8 *)M2C_FIELD(g1, u8 **, 0x64) + D_00387F2C, s8 *, 0x2C0);
    p2 = (u8 *)D_0042A574;
    addr = (M2C_FIELD(g1, s32 *, 0x58) * 4) + M2C_FIELD(p2, s32 *, 0x13C) + t0;
    if (flag != 0) {
        return *(s32 *)(addr + 0x2C);
    }
    return *(s32 *)(addr + 0x20);
}
