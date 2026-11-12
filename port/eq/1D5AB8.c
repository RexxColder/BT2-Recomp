#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387E9C;

void *func_001D5AB8(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(D_00387E9C + 0x1410);
    for (;;) {
        if (*(u8 *)(p + 0x90) == 0) {
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
