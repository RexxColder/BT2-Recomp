#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00181E98();                            /* extern */
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);            /* extern */
extern s32 *D_003877A0;

void func_00181DE8(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x140);
    D_003877A0 = temp_v0;
    memset(temp_v0, 0, 0x140);
    func_00181E98();
    *D_003877A0 = BtlTask_CreateChildList(arg0, 0xA, 0xB0);
}
