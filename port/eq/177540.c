#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387E94;

void *func_00177540(void) {
    s32 n = 0;
    u8 *p;

    p = D_00387E94;
    for (;;) {
        if (*(s32 *)(p + 0x40) == 0) {
            memset(p, 0, 0x50);
            return p;
        }
        n++;
        p += 0x50;
        if (n >= 0x64) {
            return NULL;
        }
    }
}
