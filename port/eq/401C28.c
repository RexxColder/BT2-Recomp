#include "m2c_macros.h"

void func_26E9E8(void *);
s32 func_26EB70(void *);
void func_297FE0(s32, s32, s32, s32, s32);
extern void *D_0042A590 __attribute__((section(".data")));

void func_00401C28(void) {
    s32 i;
    s32 off;

    i = 5;
    off = 0;
    do {
        i -= 1;
        func_26E9E8((u8 *)D_0042A590 + off + 0x2C);
        off += 0x28;
    } while (i >= 0);
    if (func_26EB70((u8 *)D_0042A590 + 0xF4) & 1) {
        if (func_26EB70((u8 *)D_0042A590 + 0xF4) & 8) {
            func_297FE0(2, 2, 0x20, 0x20, 1);
        }
    }
}
