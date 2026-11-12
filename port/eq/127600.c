#include "common.h"

s32 EftHit_RearmImpact(u8 *arg0) {
    u8 *p;
    s32 v1;

    if (*(s32 *)(arg0 + 0xC) == 1) {
        p = *(u8 **)(arg0 + 0x60);
        v1 = *(s32 *)(p + 4);
        if (v1 & 0x4000) {
            *(s32 *)(p + 4) = v1 & ~0x200;
        }
    }
    return 1;
}
