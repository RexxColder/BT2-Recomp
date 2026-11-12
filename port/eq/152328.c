#include "common.h"

s32 EftShot_HasTwoAttrs(s32 arg0, u64 arg1);
s32 EftShot_GetAttrPair(s32 arg0, u64 arg1, s32 arg2, s32 arg3);
s32 EftShot_GetAttrKind(s32 arg0, u64 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);

/* six attribute bits, one per (2 * index) flag bit (copied to the stack each call) */
static const s32 kAttrBits[6] = {0x2, 0x4, 0x8, 0x10, 0x20, 0x40};

s32 func_00152328(s32 arg0, s32 *arg1, s32 arg2) {
    s32 attr[6];
    s32 k;
    s32 bit;
    s32 flags;

    __builtin_memcpy(attr, kAttrBits, 24);

    if ((arg2 & 0x80) != 0) {
        arg1[0] = arg1[0] | 0x1000;
    }

    flags = arg1[0];
    if ((flags & 0x1000) != 0) {
        return flags & 0x1000;
    }

    for (k = 0; k < 6; k++) {
        bit = 1 << (2 * k);

        if ((flags & bit) == 0 && (arg2 & attr[k]) != 0) {
            arg1[0] = flags | bit;
            if (EftShot_HasTwoAttrs(arg0, attr[k]) != 0) {
                arg1[0] = arg1[0] | (1 << (2 * k + 1));
                EftShot_GetAttrPair(arg0, attr[k], (s32)&arg1[16 * k + 4], (s32)&arg1[16 * k + 12]);
            } else {
                arg1[16 * k + 4] = EftShot_GetAttrKind(arg0, attr[k]);
            }
            flags = arg1[0];
        }

        if ((flags & bit) != 0) {
            func_00208DE8(arg0, (s32)((u8 *)arg1 + 64 * k + 0x20), arg1[16 * k + 4]);
        } else if ((flags & 0x1) != 0) {
            func_00208DE8(arg0, (s32)((u8 *)arg1 + 64 * k + 0x20), arg1[4]);
        }
        flags = arg1[0];

        if ((flags & (1 << (2 * k + 1))) != 0) {
            func_00208DE8(arg0, (s32)((u8 *)arg1 + 64 * k + 0x40), arg1[16 * k + 12]);
        } else if ((flags & 0x1) != 0) {
            func_00208DE8(arg0, (s32)((u8 *)arg1 + 64 * k + 0x40), arg1[4]);
        }
        flags = arg1[0];
    }

    return 0;
}
