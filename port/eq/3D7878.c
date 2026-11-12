#include "m2c_macros.h"

void func_003D6560(void *, s32);
extern void *D_003876A4 __attribute__((section(".data")));

void func_003D7878(void *arg0) {
    if (M2C_FIELD(D_003876A4, s32 *, 0x90) < 2) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x3324) != 8) {
        return;
    }
    if (M2C_FIELD(arg0, u16 *, 0x35CC) & 1) {
        return;
    }
    if (M2C_FIELD((u8 *)arg0 + M2C_FIELD(arg0, u16 *, 0x35CE) * 32, u16 *, 0x333C) & 1) {
        return;
    }
    if (M2C_FIELD((u8 *)arg0 + M2C_FIELD(arg0, u16 *, 0x35D0) * 32, u16 *, 0x333C) & 1) {
        return;
    }
    func_003D6560(arg0, 9);
}
