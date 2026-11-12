#include "m2c_macros.h"

void *memset(void *, s32, s32);                     /* extern */

// Clears the 0x38-byte object at arg0 and sets its first word to 0.
void func_0026F888(s32 *arg0) {
    memset(arg0, 0, 0x38);
    *arg0 = 0;
}
