#include "common.h"

extern u8 D_00356080[] __attribute__((section(".data")));

/* 0x002FD6D8: over the 40 records of 0x48 bytes at D_00356080, the address of the last one whose first byte is 0;
 * NULL when there is none. */
u8 *func_002FD6D8(void) {
    u8 *a1 = NULL;
    u8 *v1 = D_00356080;
    s32 a0 = 0x27;

    do {
        s8 v = *(s8 *)v1;

        a0 = a0 - 1;
        if (v == 0) {
            a1 = v1;
        }
        v1 = v1 + 0x48;
    } while (a0 >= 0);
    return a1;
}
