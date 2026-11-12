#include "common.h"

/* 0x001CC9E8 (BT3 EftBill_Kill, fuzzy): if arg0 is a record whose +0x28 is the EftMod1CC_Update record (0x1CC770)
 * and the work at +0x38 is alive (bit 0 of its word at +0x40), set bit 0x2 there and return 1; else 0. */
s32 func_001CC9E8(u8 *arg0) {
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
    *(s32 *)(w + 0x40) = flags | 0x2;
    return 1;
}
