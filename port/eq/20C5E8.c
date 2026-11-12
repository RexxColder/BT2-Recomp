#include "common.h"

s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020C5E8(u32 arg0) {
    u8 *temp_v0;
    s32 idx;

    if (D_00387930 != 0 && arg0 < 2) {
        temp_v0 = (u8 *)func_00211288(arg0);
        idx = *(s32 *)(temp_v0 + 0x1180);
        return *(s32 *)(temp_v0 + idx * 4 + 0x1410);
    }
    return 0;
}
