#include "common.h"

extern u8 *D_003878F8;

void *func_001EA418(void) {
    u8 *g;
    u8 *p;
    s32 idx;
    s32 n;

    g = D_003878F8;
    idx = *(s32 *)(g + 0x2BC0);
    n = 0;
    for (;;) {
        p = g + (idx << 5);
        if (*(u16 *)(p + 0x14) == 0) {
            break;
        }
        idx = idx + 1;
        n = n + 1;
        if (idx >= 0x15E) {
            idx = 0;
        }
        if (n >= 0x15E) {
            return NULL;
        }
    }
    *(s32 *)(g + 0x2BC0) = idx + 1;
    if (*(s32 *)(g + 0x2BC0) >= 0x15E) {
        *(s32 *)(g + 0x2BC0) = 0;
    }
    return p;
}
