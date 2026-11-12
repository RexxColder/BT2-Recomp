#include "m2c_macros.h"

extern void *D_0036A600 __attribute__((section(".data")));

void func_00325370(s64 arg0) {
    M2C_FIELD(D_0036A600, u64 *, 0xA8) = (u64) ((u64) (arg0 << 0x20) >> 0x20);
}
