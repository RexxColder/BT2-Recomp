#include "common.h"

s32 func_002B61E0(s32 arg0);

void func_002B4C78(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = (u8 *)func_002B61E0(arg0);
    ((void (*)(s32, s32))(*(void **)(temp_v0 + 0x2C)))(*(s32 *)(temp_v0 + 0x30), arg0);
}
