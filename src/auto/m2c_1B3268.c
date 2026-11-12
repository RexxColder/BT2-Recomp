#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load16(void *, s32);              /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_00387870;
extern s32 gEftChain2List;

void func_001B3268(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x128);
    D_00387870 = temp_v0;
    memset(temp_v0, 0, 0x128);
    M2C_FIELD(D_00387870, void **, 0) = BtlPool_Alloc(BtlPool_GetCurrent(), 0xDAC0);
    memset(M2C_FIELD(D_00387870, void **, 0), 0, 0xDAC0);
    M2C_FIELD(D_00387870, s32 *, 0x10) = func_00126460(0x1F);
    EftTexSet_Load16(D_00387870 + 0x18, M2C_FIELD(D_00387870, s32 *, 0x10));
    gEftChain2List = BtlTask_CreateChildList(arg0, 6, 0xAB0);
}
