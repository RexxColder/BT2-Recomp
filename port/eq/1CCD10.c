#include "common.h"

void EftMod1CC_Update(s32 arg0);

s32 func_001CCD10(u8 *arg0, s32 arg1) {
    u8 *p;
    u8 *q;

    if (arg0 == 0) {
        return 0;
    }
    p = (u8 *)*(s32 *)(arg0 + 0x28);
    if (*(s32 *)p != (s32)0x001CC770u) { /* PS2 address of EftMod1CC_Update */
        return 0;
    }
    q = (u8 *)*(s32 *)(arg0 + 0x38);
    if ((*(s32 *)(q + 0x40) & 1) == 0) {
        return 0;
    }
    *(u8 *)(q + 0x44) = (u8)arg1;
    return 1;
}
