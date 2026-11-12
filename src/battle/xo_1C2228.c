#include "m2c_macros.h"

void func_001C2158(void *, s32);                    /* extern */
void *memset(void *, int, unsigned int);            /* extern */

/* Zeroes 0xE0 bytes at arg0, then calls func_001C2158(arg0, 0). */
void func_001C2228(void *arg0) {
    memset(arg0, 0, 0xE0);
    func_001C2158(arg0, 0);
}
