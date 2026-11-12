#include "common.h"

void func_001DFF70(u8 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);

void func_001E0048(u8 *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    func_001DFF70(arg0, *(s32 *)(arg0 + 0x21C0), arg1 & 0xFF, farg0, farg1, farg2);
}
