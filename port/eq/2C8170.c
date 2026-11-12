#include "common.h"

void func_002D1C18(u8 *arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4);

/* 0x002C8170: once obj+0xD6C is 0, copy 0x20 bytes from obj+0xD4C to a frame, zero its word 6, call func_002D1C18 with
 * (frame, frame+0x20, frame+0x24, word obj+0xD5C, word obj+0xD64); copy the frame back to obj+0xD70, set obj+0xD6C = 1,
 * obj+0xD90 / +0xD94 = the two out words. */
void func_002C8170(u8 *arg0) {
    u8 sp[0x28];
    s32 o1;
    s32 o2;
    s32 a3v;
    s32 t0v;

    if (*(s32 *)(arg0 + 0xD6C) != 0) {
        return;
    }
    memcpy(sp, arg0 + 0xD4C, 0x20);
    a3v = *(s32 *)(arg0 + 0xD5C);
    t0v = *(s32 *)(arg0 + 0xD64);
    *(s32 *)(sp + 0x18) = 0;
    func_002D1C18(sp, (s32 *)(sp + 0x20), (s32 *)(sp + 0x24), a3v, t0v);
    o1 = *(s32 *)(sp + 0x20);
    o2 = *(s32 *)(sp + 0x24);
    memcpy(arg0 + 0xD70, sp, 0x20);
    *(s32 *)(arg0 + 0xD6C) = 1;
    *(s32 *)(arg0 + 0xD90) = o1;
    *(s32 *)(arg0 + 0xD94) = o2;
}
