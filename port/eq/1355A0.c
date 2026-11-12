#include "common.h"

extern u8 *gEftBurst;

void *EftBurst_AllocPtcl(void) {
    u8 *p = gEftBurst + 0x240;
    s32 v1 = *(s32 *)(p + 0x40);
    s32 a1 = 0x15E;

    for (;;) {
        u8 *v0 = p;

        p += 0x70;
        if (v1 == 0) {
            return v0;
        }
        a1 -= 1;
        if (a1 == 0) {
            return NULL;
        }
        v1 = *(s32 *)(p + 0x40);
    }
}
