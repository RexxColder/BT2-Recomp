#include "common.h"

extern u8 **gEftShotFx;

void *func_001B5698(void) {
    u8 *p = *gEftShotFx;
    s32 v1 = *(s32 *)(p + 0xC);
    s32 a1 = 0;

    for (;;) {
        u8 *v0 = p;

        p += 0x10;
        if (v1 == 0) {
            return v0;
        }
        a1 += 1;
        if (a1 >= 5) {
            return NULL;
        }
        v1 = *(s32 *)(p + 0xC);
    }
}
