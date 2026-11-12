#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK BtlPool_SetCurrent(M2C_UNK);                /* extern */
M2C_UNK func_001329A0(M2C_UNK);                     /* extern */
M2C_UNK func_00132AB8();                            /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *gEftStage;

void func_001329D8(s32 arg0) {
    void *temp_v0;

    BtlPool_SetCurrent(2);
    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0xC);
    gEftStage = temp_v0;
    memset(temp_v0, 0, 0xC);
    M2C_FIELD(gEftStage, s32 *, 4) = arg0;
    func_00132AB8();
    func_001329A0(1);
}
