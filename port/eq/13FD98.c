#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *gEftDust;

void *func_0013FD98(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(gEftDust + 0x18);
    for (;;) {
        if (*(u8 *)(p + 0x93) == 0) {
            memset(p, 0, 0xA0);
            return p;
        }
        n++;
        p += 0xA0;
        if (n >= 0x1E) {
            return NULL;
        }
    }
}
