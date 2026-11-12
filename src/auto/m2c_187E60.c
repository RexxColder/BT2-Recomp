#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003877B4;

void func_00187E60(void) {
    memset(D_003877B4 + 0x110, 0, 0x79E0);
    M2C_FIELD(D_003877B4, s32 *, 0x7AF0) = 0;
}
