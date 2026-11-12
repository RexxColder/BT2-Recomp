#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_001A8280();                            /* extern */
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);            /* extern */
extern s32 *gEftStruggle;

void func_001A7DD0(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x638);
    gEftStruggle = temp_v0;
    memset(temp_v0, 0, 0x638);
    *gEftStruggle = BtlTask_CreateChildList(arg0, 1, 0x390);
    func_001A8280();
}
