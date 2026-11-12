#include "m2c_macros.h"

s32 func_26EB70(void *);
void func_2493C0(s32, s32, s32, s32, s32);
void func_297FE0(s32, s32, s32, s32, s32);
extern void *D_00421CF4 __attribute__((section(".data")));

void func_003C4838(void) {
    if (func_26EB70((u8 *)D_00421CF4 + 0x60) & 8) {
        func_2493C0(M2C_FIELD(D_00421CF4, s32 *, 0xC), 0x33E9, 0x3802, 0, M2C_FIELD(D_00421CF4, s32 *, 0x210));
    }
    if (func_26EB70((u8 *)D_00421CF4 + 0x60) & 0x10) {
        func_297FE0(2, 3, 0x40, 0x40, 1);
    }
    if (func_26EB70((u8 *)D_00421CF4 + 0x60) & 0x20) {
        func_297FE0(2, 4, 0x40, 0x40, 1);
    }
}
