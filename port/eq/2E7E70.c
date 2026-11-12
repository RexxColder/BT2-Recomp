#include "common.h"

void func_002E7E70(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    s32 temp_t;

    if (*(s16 *)(arg0 + 0x98) == 0) {
        *(s32 *)(arg0 + 0x48) = arg1;
        var_v1 = arg2 / (s32)*(s8 *)(arg0 + 0x0F);
        *(s32 *)(arg0 + 0x74) = 0;
    } else {
        temp_t = *(s8 *)(arg0 + 0x0D);
        *(s32 *)(arg0 + 0x48) = arg1;
        *(s32 *)(arg0 + 0x74) = 0;
        var_v1 = arg2 / (((temp_t < 0 ? temp_t + 7 : temp_t) >> 3) * (s32)*(s8 *)(arg0 + 0x0E));
    }
    *(s32 *)(arg0 + 0x4C) = var_v1;
    *(s32 *)(arg0 + 0xF4) = 0;
    *(s32 *)(arg0 + 0x90) = 0;
    *(s32 *)(arg0 + 0x94) = 0;
    *(s32 *)(arg0 + 0xF8) = 0;
}
