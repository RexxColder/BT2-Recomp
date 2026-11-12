#include "m2c_macros.h"

s32 func_26EB70(void *);
void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_00421C94 __attribute__((section(".data")));

void func_003BF210(void) {
    if (func_26EB70((u8 *)D_00421C94 + 0x470) & 8) {
        func_2493C0(M2C_FIELD(D_00421C94, s32 *, 0xC), 0x33E9, 0x3802, 0, M2C_FIELD(D_00421C94, s32 *, 0x534));
    }
}
