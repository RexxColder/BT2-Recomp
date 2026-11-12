#include "common.h"

/* 0x001CCA88 (BT3 EftBill_IsAlive, exact): 0 for a null arg0 or when arg0->0x28 is not the EftMod1CC_Update record
 * (0x001CC770); otherwise bit 0 of the word at (arg0->0x38)+0x40. */
s32 EftBill_IsAlive(u8 *arg0) {
    u8 *p;
    s32 flags;

    if (arg0 == NULL) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x28);
    if (*(s32 *)p != 0x001CC770) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x38);
    flags = *(s32 *)(p + 0x40);
    return (flags & 1) != 0;
}
