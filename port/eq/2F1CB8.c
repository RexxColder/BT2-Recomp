#include "common.h"

/* GUESS arity (5): func_002F3378 gets a0..a3 and t0 as they came in; func_002F3390 gets no arguments (a0 is
 * clobbered by the first call). */
void func_002F3378(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F3390(void);

/* 0x002F1CB8(obj, a1, a2, a3, t0): func_002F3378(obj, a1, a2, a3, t0); then obj+0xC = a3, obj+0x14 = t0, obj+0x50 = a1,
 * obj+0x54 = a2, byte obj+0x45 = 1, obj+0x10 = t0 << 11; tail-call func_002F3390. */
void func_002F1CB8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_002F3378((s32)arg0, arg1, arg2, arg3, arg4);
    *(s32 *)(arg0 + 0xC) = arg3;
    *(s32 *)(arg0 + 0x14) = arg4;
    *(s32 *)(arg0 + 0x50) = arg1;
    *(s32 *)(arg0 + 0x54) = arg2;
    arg0[0x45] = 1;
    *(s32 *)(arg0 + 0x10) = (s32)((u32)arg4 << 11);
    func_002F3390();
}
