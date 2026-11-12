#include "common.h"

/* GUESS arity: the asm passes a0..a3 (arg0, arg1, count+1, &count); ctx.h says 2 */
s32 func_002D37C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002D3700(u8 *arg0, s32 arg1) {
    s32 *cnt;
    s32 count;
    s32 idx;
    s32 v;

    cnt = (s32 *)(arg0 + 0x14);
    count = *cnt;
    idx = count % *(s32 *)(arg0 + 0x10);
    *(s32 *)(arg0 + 0x18 + idx * 4) = arg1;
    *cnt = count + 1;
    v = func_002D37C0((s32)arg0, arg1, count + 1, (s32)cnt);
    *(s32 *)(arg0 + 0x1A8) = v;
    *(s32 *)(arg0 + 0x1A4) = v;
}
