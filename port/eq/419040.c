#include "m2c_macros.h"

s32 func_003B4780(void *, void *, s32, s32, s32, s32);
void func_003B4FF8(s32);
extern void *D_0042BB80 __attribute__((section(".data")));

void func_00419040(void) {
    s32 buf[8];
    s32 off;

    off = M2C_FIELD(D_0042BB80, s32 *, 0xD4) * 4;
    buf[0] = M2C_FIELD((u8 *)D_0042BB80 + off, s32 *, 0xFC) + 0x55B;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 1;
    buf[4] = 0x3000;
    buf[5] = 2;
    M2C_FIELD(D_0042BB80, s32 *, 0xC0) = func_003B4780(buf, D_0042BB80, 1, 2, 0x3000, 2);
    func_003B4FF8(M2C_FIELD(D_0042BB80, s32 *, 0xC0));
}
