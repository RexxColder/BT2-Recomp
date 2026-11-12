#include "common.h"

void *memset(void *, int, unsigned int);
extern u8 *D_00387858;

void *func_001AF290(void) {
    s32 n = 0;
    u8 *p;

    p = *(u8 **)(D_00387858 + 0x8);
    for (;;) {
        if (*(u8 *)(p + 0x57) == 0) {
            memset(p, 0, 0x70);
            return p;
        }
        n++;
        p += 0x70;
        if (n >= 0x140) {
            return NULL;
        }
    }
}
