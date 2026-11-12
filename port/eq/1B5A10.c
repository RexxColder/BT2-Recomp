#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *gEftShotFx;

void *func_001B5A10(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(gEftShotFx + 0x4);
    for (;;) {
        if (*(s32 *)(p + 0x48) == 0) {
            memset(p, 0, 0x60);
            return p;
        }
        n++;
        p += 0x60;
        if (n >= 0x32) {
            return NULL;
        }
    }
}
