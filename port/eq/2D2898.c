#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void func_002D2948(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x002D2898(dst, src, ...): copy the 0x3C-byte block at src to dst, then tail-call func_002D2948(src, 0, src->+0x28,
 * src->+0x30, src->+0x38) (the words the copy left in a2, a3, t0; the incoming a2..t0 are overwritten). */
void func_002D2898(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    memcpy(arg0, arg1, 0x3C);
    func_002D2948(arg1, 0, *(s32 *)(arg1 + 0x28), *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x38));
}
