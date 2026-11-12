#include "common.h"

void func_002CF688(s32 arg0) {
    u8 *p = (u8 *)arg0;

    *(s32 *)(p + 8) = -3;
    *(s32 *)(p + 12) = 1;
    *(s32 *)(p + 0) = 0;
    *(s32 *)(p + 4) = 0;
}
