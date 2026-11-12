#include "m2c_macros.h"

extern u8 D_003B0C34 __attribute__((section(".data")));

// Returns 1 if the word at entry arg0 (stride 0x180) of D_003B0C34 has bit 0x4000 set.
s32 func_0028C468(s32 arg0) {
    if (*(s32 *)((u8 *)&D_003B0C34 + (arg0 * 0x180)) & 0x4000) {
        return 1;
    }
    return 0;
}
