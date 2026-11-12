#include "m2c_macros.h"

extern u8 D_003B0C34 __attribute__((section(".data")));

// Returns 1 if the word at entry arg0 (stride 0x180) of D_003B0C34 has any of bits 0x5800 set.
s32 func_0028C490(s32 arg0) {
    return (*(s32 *)((u8 *)&D_003B0C34 + (arg0 * 0x180)) & 0x5800) != 0;
}
