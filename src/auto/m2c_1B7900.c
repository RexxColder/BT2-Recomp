#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);            /* extern */
extern s32 *D_00387880;

void func_001B7900(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x3D0);
    D_00387880 = temp_v0;
    memset(temp_v0, 0, 0x3D0);
    *D_00387880 = BtlTask_CreateChildList(arg0, 4, 0x80);
}
