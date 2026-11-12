#include "m2c_macros.h"

void func_002FC550(s32);                            /* extern */
s32 sceCdLayerSearchFile(s32, s32, s32);            /* extern */
extern s32 D_0035600C __attribute__((section(".data")));

// Wraps sceCdLayerSearchFile with the 0x8000/0x8001 CD-lock calls around it.
s32 func_002FD318(s32 arg0, s32 arg1) {
    s32 temp_s0;

    func_002FC550(0x8000);
    temp_s0 = sceCdLayerSearchFile(arg0, arg1, D_0035600C);
    func_002FC550(0x8001);
    return temp_s0;
}
