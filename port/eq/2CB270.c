#include "common.h"

void func_002CB270(u8 *arg0) {
    s32 temp_v1;
    temp_v1 = *(s32 *)(arg0 + 0x5C) + 1;
    *(s32 *)(arg0 + 0x5C) = (temp_v1 < 0) ? 0 : temp_v1;
}
