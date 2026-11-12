#include "common.h"

void func_002614E0(s32 arg0, s32 arg1, s32 arg2);
void func_00261558(s32 arg0, s32 arg1);

void func_00183B78(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s0;

    s0 = *(u16 *)(arg0 + 0xB08);
    func_00261558(s0, 0);
    func_002614E0(s0, arg1, arg2);
    *(s16 *)(arg0 + 0xAD4) = (s16)arg1;
}
