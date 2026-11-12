#include "common.h"

void func_001EBC70(u8 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    *(s32 *)(arg0 + 0) = arg2;
    *(s16 *)(arg0 + 4) = arg3;
    *(s16 *)(arg0 + 6) = 0;
}
