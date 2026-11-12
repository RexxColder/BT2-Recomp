#include "m2c_macros.h"

void func_001DFF70(void *, s32, s32, f32, f32, f32);               /* extern */

/* Forwards arg0, the word at +0x21C0 and arg1 (low byte) to func_001DFF70. */
void func_001E0048(void *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    func_001DFF70(arg0, M2C_FIELD(arg0, s32 *, 0x21C0), arg1 & 0xFF, farg0, farg1, farg2);
}
