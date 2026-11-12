#include "common.h"

void func_002D7030(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    u32 a = *(u32 *)(p + 0);
    u32 b = *(u32 *)(p + 4);
    u32 c = *(u32 *)(p + 8);

    *(u32 *)(p + 8) = c - (u32)arg1;
    *(u32 *)(p + 0) = a + b * (u32)arg1;
}
