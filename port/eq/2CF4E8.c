#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002CF580(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x002CF4E8(obj, a1, out, a3, t0): when obj->+8 (count) is nonzero: r = func_002CF580(obj, a1, a3, t0); unless r is -1:
 * index = obj->+0x10 + r, wrapped by subtracting obj->+4 when it is not below obj->+4; count -= r; the 16-byte entry
 * at obj->base + 16 * index is copied to out. (The asm returns a stale v0 here: void.) */
void func_002CF4E8(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    s32 r;
    s32 idx;
    u8 *base;

    if (*(s32 *)(arg0 + 8) == 0) {
        return;
    }
    r = func_002CF580(arg0, arg1, arg3, arg4);
    if (r == -1) {
        return;
    }
    idx = *(s32 *)(arg0 + 0x10) + r;
    if (!(idx < *(s32 *)(arg0 + 4))) {
        idx = idx - *(s32 *)(arg0 + 4);
    }
    *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) - r;
    *(s32 *)(arg0 + 0x10) = idx;
    base = *(u8 **)arg0;
    memcpy(arg2, base + idx * 16, 16);
}
