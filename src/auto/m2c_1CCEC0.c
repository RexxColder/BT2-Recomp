#include "m2c_macros.h"

M2C_UNK BtlPool_Free(s32, s32);                     /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK func_001CCE30();                            /* extern */
extern s32 D_003878C8;

void func_001CCEC0(void) {
    func_001CCE30();
    BtlPool_Free(BtlPool_GetCurrent(), D_003878C8);
    D_003878C8 = 0;
}
