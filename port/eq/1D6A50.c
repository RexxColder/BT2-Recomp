#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387E9C;

void *func_001D6A50(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(D_00387E9C + 0x1418);
    for (;;) {
        if (*(u8 *)(p + 0x4B) == 0) {
            memset(p, 0, 0x50);
            return p;
        }
        n++;
        p += 0x50;
        if (n >= 0x19) {
            return NULL;
        }
    }
}
