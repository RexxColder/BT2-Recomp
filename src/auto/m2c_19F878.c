#include "m2c_macros.h"

M2C_UNK BtlPool_Free(s32, s32);                     /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK func_0019F7F0();                            /* extern */
extern s32 D_003877F8;

void func_0019F878(void) {
    func_0019F7F0();
    BtlPool_Free(BtlPool_GetCurrent(), D_003877F8);
    D_003877F8 = 0;
}
