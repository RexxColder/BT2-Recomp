#include "m2c_macros.h"

s32 BtlPool_Alloc(s32, M2C_UNK);                    /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
M2C_UNK sceVu0UnitMatrix(s32);                      /* extern */
extern s32 D_00387714;

void func_0012E888(void) {
    s32 temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x50);
    D_00387714 = temp_v0;
    memset(temp_v0, 0, 0x50);
    sceVu0UnitMatrix(D_00387714);
}
