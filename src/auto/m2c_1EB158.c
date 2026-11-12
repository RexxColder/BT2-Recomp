#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_00387908;

void func_001EB158(void) {
    memset(D_00387908, 0, 0x200);
    M2C_FIELD(D_00387908, s32 *, 0x200) = 0;
}
