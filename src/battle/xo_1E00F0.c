#include "m2c_macros.h"

void func_001E0068(void *, s32, s32);               /* extern */

/* Forwards arg0, the word at +0x21C0 and arg1 (low byte) to func_001E0068. */
void func_001E00F0(void *arg0, s32 arg1) {
    func_001E0068(arg0, M2C_FIELD(arg0, s32 *, 0x21C0), arg1 & 0xFF);
}
