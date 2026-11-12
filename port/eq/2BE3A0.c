#include "common.h"

s32 func_002BF2C0(s32 arg0);

s32 func_002BE3A0(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 temp_v0;

    temp_v0 = func_002BF2C0(arg0);
    if (temp_v0 != 0) {
        *arg1 = *(s32 *)(temp_v0 + 0xC);
        *arg2 = *(s32 *)(temp_v0 + 0x10);
        return 0;
    }
    return -1;
}
