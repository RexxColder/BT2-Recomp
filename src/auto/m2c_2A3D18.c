#include "m2c_macros.h"

extern void *D_003B0F6C __attribute__((section(".data")));

void *func_002A3D18(void) {
    if (D_003B0F6C == NULL) {
        return NULL;
    }
    return D_003B0F6C + (((u32) M2C_FIELD(D_003B0F6C, u32 *, 4) >> 2) * 4);
}
