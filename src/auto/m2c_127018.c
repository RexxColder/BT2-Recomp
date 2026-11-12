#include "m2c_macros.h"

s32 BtlPool_Alloc(s32, M2C_UNK);                    /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK EftHitArena_Init();                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 gEftHitList;

void func_00127018(void) {
    s32 temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x6010);
    gEftHitList = temp_v0;
    memset(temp_v0, 0, 0x6010);
    EftHitArena_Init();
}
