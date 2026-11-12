#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_00387798;

void func_00180658(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x10);
    D_00387798 = temp_v0;
    memset(temp_v0, 0, 0x10);
    M2C_FIELD(D_00387798, s32 *, 0xC) = BtlTask_CreateChildList(arg0, 0x1E, 0x70);
}
