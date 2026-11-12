#include "common.h"

void func_001DFE00(u8 *arg0, s32 arg1, s32 arg2, f32 farg0);

void func_001DFE98(u8 *arg0, s32 arg1, f32 farg0) {
    func_001DFE00(arg0, *(s32 *)(arg0 + 0x21C0), arg1 & 0xFF, farg0);
}
