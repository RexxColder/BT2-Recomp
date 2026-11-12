#include "m2c_macros.h"

M2C_UNK *BtlPool_Alloc(s32, M2C_UNK);               /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_003877CC;
extern M2C_UNK *gEftDisc;

void func_00194C30(s32 arg0) {
    M2C_UNK *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0xC);
    gEftDisc = temp_v0;
    memset(temp_v0, 0, 0xC);
    *gEftDisc = BtlPool_Alloc(BtlPool_GetCurrent(), 0x10680);
    memset(*gEftDisc, 0, 0x10680);
    D_003877CC = BtlTask_CreateChildList(arg0, 0xA, 0x1F0);
}
