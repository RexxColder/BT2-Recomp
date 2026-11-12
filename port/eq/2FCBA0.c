#include "common.h"

void func_00325830(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
extern s32 D_003553E4 __attribute__((section(".data")));
extern u8 D_0037E190[] __attribute__((section(".data")));

void func_002FCBA0(s32 arg0_unused, u8 *arg1, s32 arg2, s32 arg3) {
    s32 a3 = arg3;
    s32 i;

    if (arg2 > 0) {
        a3 = -0x56;
        for (i = 0; i < arg2; i++) {
            arg1[i] = 0xAA;
        }
    }
    func_00325830(arg1, D_0037E190, D_003553E4, a3);
    D_003553E4 += 1;
}
