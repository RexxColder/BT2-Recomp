#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load32(void *, s32);              /* extern */
s32 func_00126460(s32);                             /* extern */
extern s32 D_003878A8;
extern void *D_003878AC;

void func_001C7798(s32 arg0) {
    D_003878AC = BtlPool_Alloc(BtlPool_GetCurrent(), 0x210);
    EftTexSet_Load32(D_003878AC, func_00126460(D_003878A8));
    M2C_FIELD(D_003878AC, s32 *, 0x208) = BtlTask_CreateChildList(arg0, 0x23, 0x3D0);
}
