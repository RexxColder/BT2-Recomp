#include "m2c_macros.h"

extern void *D_003B0F70 __attribute__((section(".data")));

void *func_002A3D70(void) {
    if (D_003B0F70 == NULL) {
        return NULL;
    }
    return D_003B0F70 + (((u32) M2C_FIELD(D_003B0F70, u32 *, 4) >> 2) * 4);
}
