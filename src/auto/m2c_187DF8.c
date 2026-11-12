#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003877B4;

void func_00187DF8(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x7B00);
    D_003877B4 = temp_v0;
    memset(temp_v0, 0, 0x7B00);
    M2C_FIELD(D_003877B4, s32 *, 0x7AF4) = BtlTask_CreateChildList(arg0, 0xC, 0x1F0);
}
