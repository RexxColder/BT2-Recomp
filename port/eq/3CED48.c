#include "m2c_macros.h"

s32 func_26EB70(void *);
void func_297FE0(s32, s32, s32, s32, s32);
void func_26E9E8(void *);
extern void *D_0042311C __attribute__((section(".data")));

void func_003CED48(void) {
    s32 i;
    s32 off;

    if (func_26EB70((u8 *)D_0042311C + 0x8C) & 8) {
        func_297FE0(2, 8, 0x40, 0x40, 1);
    }
    i = 3;
    off = 0;
    do {
        i -= 1;
        func_26E9E8((u8 *)D_0042311C + off + 0x14);
        off += 0x28;
    } while (i >= 0);
}
