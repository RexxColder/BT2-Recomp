#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387E94;

void *func_00177980(void) {
    s32 n = 0;
    u8 *p;

    p = D_00387E94 + 0x1F40;
    for (;;) {
        if (*(s32 *)(p + 0x44) == 0) {
            memset(p, 0, 0x60);
            return p;
        }
        n++;
        p += 0x60;
        if (n >= 0x50) {
            return NULL;
        }
    }
}
