#include "m2c_macros.h"

extern void *D_003B0F68 __attribute__((section(".data")));

void *func_002A3CC0(void) {
    if (D_003B0F68 == NULL) {
        return NULL;
    }
    return D_003B0F68 + (((u32) M2C_FIELD(D_003B0F68, u32 *, 4) >> 2) * 4);
}
