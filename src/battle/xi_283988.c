#include "m2c_macros.h"

extern u8 D_00388DB0 __attribute__((section(".data")));

// Clears the word at entry arg0 (stride 0x30, arg0 < 8) of the lens table D_00388DB0.
void GfxLens_Stop(u32 arg0) {
    if (arg0 < 8U) {
        *(s32 *)((u8 *)&D_00388DB0 + (arg0 * 0x30)) = 0;
    }
}
