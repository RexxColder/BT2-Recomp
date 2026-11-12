#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(s32);                       /* extern */

void func_001B78C0(void *arg0) {
    BtlTask_SetDead(M2C_FIELD(arg0, s32 *, 0x70));
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
}
