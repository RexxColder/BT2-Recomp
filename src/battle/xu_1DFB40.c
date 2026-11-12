#include "common.h"

void func_001DFA50(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

/* Passes arg0, arg1, arg3 and f12 (farg0, an incoming float param) to func_001DFA50, then stores arg2 at +0x21C0 and clears the byte at +0x21DA. */
void func_001DFB40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    func_001DFA50(arg0, arg1, arg3, farg0);
    *(s32 *)(arg0 + 0x21C0) = arg2;
    *(u8 *)(arg0 + 0x21DA) = 0;
}
