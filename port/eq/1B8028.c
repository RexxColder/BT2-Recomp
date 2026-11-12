#include "common.h"

void *memset(void *, int, unsigned int);

void *func_001B8028(u8 *arg0) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(arg0 + 0x68);
    for (;;) {
        if (*(s32 *)(p + 0x5C) & 1) {
            n++;
            p += 0x60;
            if (n >= 0xA) {
                return NULL;
            }
            continue;
        }
        memset(p, 0, 0x60);
        return p;
    }
}
