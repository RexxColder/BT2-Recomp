#include "common.h"

void *func_002B61E0(void);

void func_002BCDA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;

    temp_v0 = func_002B61E0();
    *(s32 *)(temp_v0 + 0x4C) = arg3;
    *(s32 *)(temp_v0 + 0x40) = arg0;
    *(s32 *)(temp_v0 + 0x44) = arg1;
    *(s32 *)(temp_v0 + 0x48) = arg2;
}
