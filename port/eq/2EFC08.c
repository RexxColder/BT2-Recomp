#include "common.h"

s32 func_00306798(s32 arg0, s32 arg1);

u32 func_002EFC08(u8 *arg0, s32 arg1) {
    u8 *ent = *(u8 **)(arg0 + 0xC) + arg1 * 4;
    u8 *p = *(u8 **)(ent + 8);
    u32 v = func_00306798(*(s32 *)(p + 4), 0);

    return v >> 1;
}
