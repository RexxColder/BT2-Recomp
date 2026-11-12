#include "m2c_macros.h"

s32 func_002C0EA8(void *, s32);                             /* extern */

s32 func_002CEDA0(void *arg0) {
    return func_002C0EA8(arg0, M2C_FIELD(arg0, s32 *, 0x1F44)) != 0;
}
