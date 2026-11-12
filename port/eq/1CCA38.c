#include "common.h"

void EftMod1CC_Update(s32 arg0);

s32 func_001CCA38(u8 *arg0) {
    u8 *p;
    u8 *q;
    s32 v;

    if (arg0 == 0) {
        return 0;
    }
    p = (u8 *)*(s32 *)(arg0 + 0x28);
    if (*(s32 *)p != (s32)0x001CC770u) { /* PS2 address of EftMod1CC_Update */
        return 0;
    }
    q = (u8 *)*(s32 *)(arg0 + 0x38);
    v = *(s32 *)(q + 0x40);
    if ((v & 1) == 0) {
        return 0;
    }
    *(s32 *)(q + 0x40) = v | 0x4;
    return 1;
}
