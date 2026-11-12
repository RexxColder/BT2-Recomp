#include "common.h"

s32 func_00269CD8(s32 arg0, s32 arg1) {
    u8 *self;
    s32 flags;
    s64 m;
    s32 a;
    s32 r;

    self = (u8 *)arg0;
    flags = *(s32 *)(*(u8 **)(self + 0x44));
    m = *(s64 *)(self + 0xAF0);
    a = arg1;
    r = 1;

    if ((flags & 0x10000) != 0) {
        if ((m & 0x102) == 0x102) {
            if ((u32)(a - 0x23) < 10u) {
                r = 0;
            } else if (a == 0x40 || a == 0x41 || a == 0x42 || a == 0x43) {
                r = 0;
            }
        } else if ((u32)(a - 0x15) < 10u) {
            r = ((m & 0x42) == 0x42) ? 0 : 1;
        } else if ((u32)(a - 0x23) < 10u) {
            r = ((m & 0x22) == 0x22) ? 0 : 1;
        } else if (a == 0x42) {
            r = ((m & 0x22) == 0x22) ? 1 : 0;
        } else if (a == 0x43) {
            r = ((m & 0x42) == 0x42) ? 1 : 0;
        }
    } else if ((flags & 0x20000) != 0) {
        if ((u32)(a - 0x23) < 10u) {
            r = ((m & 0x22) == 0x22) ? 0 : 1;
        } else if (a == 0x40) {
            r = ((m & 0x22) == 0x22) ? 1 : 0;
        }
    } else if ((flags & 0x40000) != 0) {
        if ((u32)(a - 0x23) < 10u) {
            r = ((m & 0x42) == 0x42) ? 0 : 1;
        } else if ((u32)(a - 0x15) < 10u) {
            r = ((m & 0x22) == 0x22) ? 0 : 1;
        } else if (a == 0x40) {
            r = ((m & 0x22) == 0x22) ? 1 : 0;
        } else if (a == 0x41) {
            r = ((m & 0x42) == 0x42) ? 1 : 0;
        } else if (a == 0x42) {
            r = ((m & 0x22) == 0x22) ? 0 : 1;
        } else if (a == 0x43) {
            r = ((m & 0x42) == 0x42) ? 0 : 1;
        }
    } else {
        if (a == 0x40) {
            r = ((m & 0x22) == 0x22) ? 1 : 0;
        } else if (a == 0x41) {
            r = ((m & 0x42) == 0x42) ? 1 : 0;
        } else if (a == 0x42) {
            r = ((m & 0x22) == 0x22) ? 0 : 1;
        } else if (a == 0x43) {
            r = ((m & 0x42) == 0x42) ? 0 : 1;
        } else if (a == 0x6F) {
            r = ((~m & 0x82) != 0) ? 0 : 1;
        }
    }
    return r;
}
