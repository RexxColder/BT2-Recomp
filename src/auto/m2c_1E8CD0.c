#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003878F8;

void func_001E8CD0(void) {
    memset(D_003878F8, 0, 0x2BC0);
    M2C_FIELD(D_003878F8, s32 *, 0x2BC0) = 0;
}
