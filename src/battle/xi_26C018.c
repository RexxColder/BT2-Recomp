#include "m2c_macros.h"

void *memset(void *, s32, s32);                     /* extern */

// Clears 0x44 bytes at the address the caller passes in a0 (tail call to memset with a1 = 0).
void *func_0026C018(void *arg0) {
    return memset(arg0, 0, 0x44);
}
