#include "common.h"

extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_0028C3D8(s32 arg0) {
    s32 off;
    u8 *p;
    s32 v;
    s32 flags;

    off = arg0 * 0x180;
    p = D_003B0B00 + off + 0x140;
    flags = *(s32 *)(p + 0x4);
    if (flags & 0x10) {
        v = *(s32 *)(p + 0x8);
        if (v > 0) {
            *(s32 *)(p + 0x8) = v - 1;
        }
        return 0;
    }
    if (flags & 0x40) {
        v = *(s32 *)(p + 0x8);
        if (v <= 0) {
            *(s32 *)(p + 0x8) = v + 1;
        }
        return 0;
    }
    flags = *(s32 *)(D_003B0B00 + off + 0x134);
    if (flags & 0x4000) {
        return 1;
    }
    if (flags & 0x1000) {
        return -1;
    }
    return 0;
}
