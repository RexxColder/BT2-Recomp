#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_0042FD78 __attribute__((section(".data")));

void func_004209F0(void) {
    u8 *a2 = *(u8 **)0x003876A4;
    s32 v0 = *(s32 *)(a2 + 0x30);
    s32 v1 = M2C_FIELD(D_0042FD78, s32 *, 0xB8);

    func_2493C0(0, 0x1F39, 0x332F, 0, (v0 * 6) + v1 + 1);
}
