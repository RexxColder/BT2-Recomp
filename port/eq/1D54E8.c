#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387E9C;

void *func_001D54E8(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(D_00387E9C + 0x140C);
    for (;;) {
        if (*(u8 *)(p + 0x5B) == 0) {
            memset(p, 0, 0x60);
            return p;
        }
        n++;
        p += 0x60;
        if (n >= 0x12) {
            return NULL;
        }
    }
}
