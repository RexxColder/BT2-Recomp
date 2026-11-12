#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003877B0;

void func_00184068(void) {
    memset(D_003877B0, 0, 0x79E0);
    M2C_FIELD(D_003877B0, s32 *, 0x79E0) = 0;
}
