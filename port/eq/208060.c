#include "common.h"

s32 func_00202DA0(s32 arg0, s32 arg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_00208060(u32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_r1;
    s32 temp_r2;

    if (D_00387930 != 0 && arg0 < 2U) {
        temp_v0 = func_00211288(arg0);
        temp_r1 = func_00202DA0(temp_v0, arg1);
        temp_s0 = *(s32 *)temp_r1 * 9;
        temp_r2 = func_00202DA0(temp_v0, arg1);
        return temp_s0 + *(s32 *)(temp_r2 + 4);
    }
    return 0;
}
