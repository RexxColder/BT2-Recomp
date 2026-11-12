#include "common.h"

void *memset(void *s, s32 c, u32 n);
extern u8 *D_00387E9C;

void func_001D2FD8(void) {
    u8 *p = D_00387E9C;
    u8 *a0;
    s32 n = 0x1F;

    do {
        a0 = p;
        p += 0xA0;
        n -= 1;
        memset(a0, 0, 0xA0);
    } while (n >= 0);
}
