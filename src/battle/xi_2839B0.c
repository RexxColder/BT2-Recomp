#include "m2c_macros.h"

extern u8 D_00388DC4 __attribute__((section(".data")));

// Stores arg1 at entry arg0 (stride 0x30, arg0 < 8) of the lens table D_00388DC4 (hold value).
void GfxLens_SetHold(u32 arg0, s32 arg1) {
    if (arg0 < 8U) {
        *(s32 *)((u8 *)&D_00388DC4 + (arg0 * 0x30)) = arg1;
    }
}
