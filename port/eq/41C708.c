#include "m2c_macros.h"

void func_297FE0(s32, s32, s32, s32, s32);
extern s32 D_003B0C34 __attribute__((section(".data")));
extern void *D_0042FD70 __attribute__((section(".data")));

void func_0041C708(void) {
    if (D_003B0C34 & 8) {
        M2C_FIELD(D_0042FD70, s32 *, 0x74) |= 1;
        M2C_FIELD(D_0042FD70, s32 *, 0x74) |= 2;
        M2C_FIELD(D_0042FD70, s32 *, 0x80) = 0xF;
        func_297FE0(0, 1, 0x40, 0x40, 1);
    }
}
