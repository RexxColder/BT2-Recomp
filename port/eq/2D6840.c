#include "common.h"

s32 func_002D5BF8(u8 *arg0, s32 arg1, s32 arg2);

/* 0x002D6840(obj, src, a2, table, idx): e = table + 16 * idx; e->+4 = a2; e->+8 = src->+0x44; r = func_002D5BF8(obj,
 * src->+0x44, a2); e->+0xC = r == 1 ? src->+0x48 / 2 (rounded toward zero) : src->+0x48; e->+0x10 = obj->+8 when
 * nonzero, else src->+0x44. */
void func_002D6840(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, s32 arg4) {
    u8 *e = arg3 + (arg4 << 4);
    s32 r;
    s32 v;

    *(s32 *)(e + 4) = arg2;
    *(s32 *)(e + 8) = *(s32 *)(arg1 + 0x44);
    r = func_002D5BF8(arg0, *(s32 *)(arg1 + 0x44), arg2);
    if (r == 1) {
        v = *(s32 *)(arg1 + 0x48);
        *(s32 *)(e + 0xC) = v / 2;
    } else {
        *(s32 *)(e + 0xC) = *(s32 *)(arg1 + 0x48);
    }
    if (*(s32 *)(arg0 + 8) != 0) {
        *(s32 *)(e + 0x10) = *(s32 *)(arg0 + 8);
    } else {
        *(s32 *)(e + 0x10) = *(s32 *)(arg1 + 0x44);
    }
}
