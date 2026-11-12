#include "common.h"

s32 func_002F8E88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002F8EB8(s32 arg0);

s32 func_002E8060(u8 *arg0, s32 arg1) {
    s32 temp_s0;
    u8 *temp_v1;
    s32 a3;
    s32 t0;

    temp_v1 = arg0 + 0x48;
    temp_s0 = *(s32 *)(arg0 + 8);
    a3 = *(s32 *)(temp_v1 + 0x14) + (*(s32 *)(temp_v1 + 0x20) << 1);
    t0 = a3 + (*(s32 *)(temp_v1 + 0x1C) << 1);
    func_002F8E88(temp_s0, *(s32 *)(arg0 + 0x48), arg1, a3, t0);
    return func_002F8EB8(temp_s0);
}
