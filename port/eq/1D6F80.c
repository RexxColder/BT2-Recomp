#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387E9C;

void *func_001D6F80(void) {
    u32 count;
    u32 i;
    u8 *p;

    count = *(u32 *)(D_00387E9C + 0x16B8);
    if (count == 0) {
        return NULL;
    }
    p = *(u8 **)(D_00387E9C + 0x141C);
    i = 0;
    for (;;) {
        if (p[0x67] == 0) {
            memset(p, 0, 0x70);
            return p;
        }
        i += 1;
        p += 0x70;
        if (!(i < count)) {
            return NULL;
        }
    }
}
