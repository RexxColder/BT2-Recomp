#include "common.h"

/* The original returns the callee's stale v0 (a loop-compare leftover); treated as void. */
void func_001DFA50(u8 *arg0, s32 arg1, s32 arg2, f32 farg3);

void func_001DFB40(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    func_001DFA50(arg0, arg1, arg3, farg0);
    *(s32 *)(arg0 + 0x21C0) = arg2;
    *(u8 *)(arg0 + 0x21DA) = 0;
}
