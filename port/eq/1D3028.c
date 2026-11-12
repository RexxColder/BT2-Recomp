#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387E9C;

void *func_001D3028(void) {
    s32 n = 0;
    u8 *p;

    p = D_00387E9C;
    for (;;) {
        if (*(u8 *)(p + 0x99) == 0) {
            memset(p, 0, 0xA0);
            return p;
        }
        n++;
        p += 0xA0;
        if (n >= 0x20) {
            return NULL;
        }
    }
}
