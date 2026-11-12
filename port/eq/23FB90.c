#include "common.h"

/* 0x0023FB90: p = a0->+0x1530; q = p->+0x958; s0 = q->+0x8C / 30; return s0 + func_001F9848(a0). */
s32 func_001F9848(s32 arg0);

s32 func_0023FB90(s32 a0) {
    u8 *a1;
    u8 *v1;
    s32 s0;

    a1 = *(u8 **)(a0 + 0x1530);
    v1 = *(u8 **)(a1 + 0x958);
    s0 = *(s32 *)(v1 + 0x8C) / 30;
    return s0 + func_001F9848(a0);
}
