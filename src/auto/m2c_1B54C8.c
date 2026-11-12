#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
extern s32 *D_0038787C;

void func_001B54C8(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 4);
    D_0038787C = temp_v0;
    *temp_v0 = 0;
    *D_0038787C = BtlTask_CreateChildList(arg0, 3, 0x60);
}
