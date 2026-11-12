#include "m2c_macros.h"

s32 BtlPool_Alloc(s32, M2C_UNK);                    /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_0038780C;
extern s32 D_00387810;

void func_001A10D0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 8);
    D_0038780C = temp_v0;
    memset(temp_v0, 0, 8);
    D_00387810 = BtlTask_CreateChildList(arg0, 2, 0xA70);
}
