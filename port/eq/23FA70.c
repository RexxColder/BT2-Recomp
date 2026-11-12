#include "common.h"

/* 0x0023FA70: return (*(s32 *)(*(a0 + 0x1530) + 0x958) + 0x78 field) / 30 + func_001F97A8(a0). */
s32 func_001F97A8(s32 arg0);

s32 func_0023FA70(s32 a0) {
    u8 *p;
    s32 q;

    p = *(u8 **)((u8 *)a0 + 0x1530);
    q = *(s32 *)(*(u8 **)(p + 0x958) + 0x78) / 30;
    return q + func_001F97A8(a0);
}
