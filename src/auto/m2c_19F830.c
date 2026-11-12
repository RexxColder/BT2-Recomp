#include "m2c_macros.h"

s32 BtlPool_Alloc(s32, M2C_UNK);                    /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK func_0019D848();                            /* extern */
M2C_UNK func_0019F688();                            /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_003877F8;

void func_0019F830(void) {
    s32 temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x1F4);
    D_003877F8 = temp_v0;
    memset(temp_v0, 0, 0x1F4);
    func_0019D848();
    func_0019F688();
}
