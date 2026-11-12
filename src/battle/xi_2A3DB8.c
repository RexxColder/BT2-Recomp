#include "m2c_macros.h"

extern u8 D_003B1FF0 __attribute__((section(".data")));

// Returns the address of entry arg0 (stride 0x28) of D_003B1FF0.
void *func_002A3DB8(s32 arg0) {
    return &D_003B1FF0 + (arg0 * 0x28);
}
