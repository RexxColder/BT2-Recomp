#include "common.h"

/* 0x001CCCC0 (sibling of 0x001CC9E8, BT3 EftBill_Kill, fuzzy): as func_001CC9E8 but sets bit 0x10 of the work flags. */
s32 func_001CCCC0(u8 *arg0) {
    u8 *w;
    s32 flags;

    if (arg0 == NULL) {
        return 0;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != 0x001CC770) {
        return 0;
    }
    w = *(u8 **)(arg0 + 0x38);
    flags = *(s32 *)(w + 0x40);
    if ((flags & 0x1) == 0) {
        return 0;
    }
    *(s32 *)(w + 0x40) = flags | 0x10;
    return 1;
}
