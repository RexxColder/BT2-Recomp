#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
extern s32 *D_003878C0;
extern s32 D_003878C4;

void func_001CC8E8(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 4);
    D_003878C0 = temp_v0;
    *temp_v0 = 0;
    D_003878C4 = BtlTask_CreateChildList(arg0, 0x14, 0xD0);
}
