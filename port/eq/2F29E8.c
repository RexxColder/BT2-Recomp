#include "common.h"

s32 func_002F33A8(void *arg0);
void func_002F2718(void *arg0);
extern s32 D_00353F84 __attribute__((section(".data")));
extern s8 D_00353F90 __attribute__((section(".data")));

/* 0x002F29E8: if func_002F33A8(&D_00353F84) is nonzero, call func_002F2718 on every 0x60-byte
 * record (40 of them, from D_00353F90) whose first byte is 1, then clear D_00353F84. */
void func_002F29E8(void) {
    s32 i;
    s8 *p;

    if (func_002F33A8(&D_00353F84) != 0) {
        p = &D_00353F90;
        i = 0x27;
        do {
            if (*p == 1) {
                func_002F2718(p);
            }
            i -= 1;
            p += 0x60;
        } while (i >= 0);
        D_00353F84 = 0;
    }
}
