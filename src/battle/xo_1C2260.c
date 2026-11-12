#include "m2c_macros.h"

void func_001C2158(void *, s32);                    /* extern */
void *memset(void *, int, unsigned int);            /* extern */

/* Zeroes 0xF0 bytes at arg0, then calls func_001C2158(arg0, 1). */
void func_001C2260(void *arg0) {
    memset(arg0, 0, 0xF0);
    func_001C2158(arg0, 1);
}
