#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))

void func_002D1DF0(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    u32 t0 = FLD(arg1, 0xC);
    u32 t4 = FLD(arg1, 0x10);
    u32 t2 = FLD(arg1, 0x8);
    u32 t1 = FLD(arg1, 0x14) + FLD(arg1, 0x18);
    s32 h = *(s16 *)(arg1 + 0x1E);
    s32 q = (s32)t0 / 10;
    u32 v;

    v = (((t4 * 0xC) + (u32)q) * 2) + (t2 * 0x15114) + (t0 * 0x59E) + t1;
    *arg2 = (s32)((v * 0x3E8) + ((u32)h * 0x1F4));
    *arg3 = arg0;
}
