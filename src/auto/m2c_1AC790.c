#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load4(void *, s32);               /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_0038784C;

void func_001AC790(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x58);
    D_0038784C = temp_v0;
    memset(temp_v0, 0, 0x58);
    M2C_FIELD(D_0038784C, s32 *, 0x50) = func_00126460(0x10F);
    M2C_FIELD(D_0038784C, s32 *, 0x54) = func_00126460(0x110);
    EftTexSet_Load4(D_0038784C + 8, func_00126460(0x111));
    M2C_FIELD(D_0038784C, s32 *, 0) = BtlTask_CreateChildList(arg0, 0xA, 0x1D0);
}
