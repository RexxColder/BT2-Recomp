#include "common.h"

void func_002BF120(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002BF088(s32 arg0, s32 arg1) {
    s32 temp_v1;
    s32 temp_a3;

    temp_v1 = *(s32 *)(arg0 + 0x2004);
    *(s32 *)(temp_v1 + 0x2C) = arg1;
    temp_a3 = *(s32 *)temp_v1;
    if ((arg1 != 0) || (*(s32 *)(arg0 + 0x50) != 1)) {
        func_002BF120(temp_a3, arg0 + 0x1020, arg1, temp_a3);
    }
}
