#include "m2c_macros.h"

void *memset(void *, s32, s32);                     /* extern */

// Clears 0x22 bytes at the fixed address 0 of the caller's argument register a0 (tail call with a1 = 0).
void *func_00298528(void *arg0) {
    return memset(arg0, 0, 0x22);
}
