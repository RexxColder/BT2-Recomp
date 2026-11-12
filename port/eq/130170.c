#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *gEftBubble;

void *func_00130170(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(gEftBubble + 0x4);
    for (;;) {
        if (*(u8 *)(p + 0x55) == 0) {
            memset(p, 0, 0x60);
            return p;
        }
        n++;
        p += 0x60;
        if (n >= 0x64) {
            return NULL;
        }
    }
}
