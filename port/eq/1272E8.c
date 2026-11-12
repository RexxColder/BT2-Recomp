#include "common.h"

extern u8 *gEftHitList;

s32 func_001272E8(u32 arg0) {
    s32 v0 = 0;
    u8 *p;

    if (gEftHitList == NULL) {
        return 0;
    }
    if (arg0 < *(u32 *)(gEftHitList + 0x6000)) {
        p = *(u8 **)(gEftHitList + arg0 * 0x180 + 0x60);
        if (p != NULL) {
            v0 = *(s32 *)(p + 4);
        }
    }
    return v0;
}
