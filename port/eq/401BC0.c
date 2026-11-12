#include "m2c_macros.h"

s32 func_26EB60(void *);
void func_297FE0(s32, s32, s32, s32, s32);
extern void *D_0042A590 __attribute__((section(".data")));

void func_00401BC0(void) {
    if ((func_26EB60((u8 *)D_0042A590 + 0xCC) != 0) && (*(s32 *)0x003B0C34 & 0x4000)) {
        M2C_FIELD(D_0042A590, s32 *, 0x220) = 1;
        func_297FE0(2, 9, 0x40, 0x40, 1);
    }
}
