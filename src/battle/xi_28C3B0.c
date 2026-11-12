#include "m2c_macros.h"

extern u8 D_003B0C48 __attribute__((section(".data")));

// Sets the word at entry arg0 (stride 0x180) of D_003B0C48 to 1.
void func_0028C3B0(s32 arg0) {
    *(s32 *)((u8 *)&D_003B0C48 + (arg0 * 0x180)) = 1;
}
