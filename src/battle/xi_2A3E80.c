#include "m2c_macros.h"

extern u8 D_003B0F7C __attribute__((section(".data")));

// Returns the address of entry arg0 (stride 0x68) of D_003B0F7C.
void *func_002A3E80(s32 arg0) {
    return &D_003B0F7C + (arg0 * 0x68);
}
