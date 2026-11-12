#include "common.h"

void EftObj_SetMtx(s32 arg0, s32 arg1);
s32 Rand_Range(s32 arg0);
s32 func_002B5CB8(s32 arg0);
s32 func_002B8280(s32 arg0, s32 arg1);
s32 func_002B8328(s32 arg0);
extern u8 D_00379618[] __attribute__((section(".data")));
extern u8 D_00379650[] __attribute__((section(".data")));
extern u8 D_00379698[] __attribute__((section(".data")));

void func_002B9B18(s32 arg0, s32 arg1) {
    s32 s0;
    s32 r;

    s0 = arg1;
    if (func_002B8280(arg0, arg1) != 1) {
        Rand_Range((s32)D_00379618);
        return;
    }
    if (*(s32 *)(arg0 + 0x17C) == 0) {
        if (arg1 == 0x101) {
            Rand_Range((s32)D_00379650);
            return;
        }
        if (arg1 == 0) {
            Rand_Range((s32)D_00379698);
            return;
        }
    }
    *(s32 *)(arg0 + 0x4C) = arg1;
    if (func_002B8328(arg0) == 2 && arg1 == 0) {
        r = func_002B5CB8(arg0);
        s0 = (~r == 0) ? 0x11 : r;
    }
    EftObj_SetMtx(arg0, s0);
}
