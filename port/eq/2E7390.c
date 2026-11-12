#include "common.h"

s32 func_002E7390(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    u8 *p;

    p = (u8 *)arg0;
    *arg1 = *(s32 *)(p + 0x8C);
    *arg2 = *(s32 *)(p + 0x40) - *(s32 *)(p + 0x8C);
    *arg3 = *(s32 *)(p + 0x18) - *(s32 *)(p + 0x88);
    return *(s32 *)(p + 0x3C);
}
