#include "common.h"

extern u8 D_003B0F40[] __attribute__((section(".data")));

void func_002A3D90(s32 arg0, s32 arg1, f32 farg0) {
    u8 *base = D_003B0F40 + 8;

    *(u8 *)(base + arg0 + 0x1640) = (u8)arg1;
    *(f32 *)(base + arg0 * 4 + 0x1650) = farg0;
}
