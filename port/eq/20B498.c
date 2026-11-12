#include "common.h"

s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020B498(u32 arg0) {
    u8 *temp_v0;

    if (D_00387930 != 0 && arg0 < 2) {
        temp_v0 = (u8 *)func_00211288(arg0);
        if (*(s32 *)(temp_v0 + 0x142C) >= 0) {
            return *(s32 *)(temp_v0 + 0x1430);
        }
    }
    return -1;
}
