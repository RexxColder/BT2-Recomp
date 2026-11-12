#include "common.h"

extern u8 *D_003876A0;
void func_0029BAB0(u8 *a0, u8 *a1);

void func_0027A9E8(u8 *arg0) {
    if (*(s64 *)(D_003876A0 + 0x4D8) & 3) {
        *(s32 *)(arg0 + 0x50) = 0;
        *(s8 *)(arg0 + 0x54) = 0;
        func_0029BAB0(arg0 + 0x58, arg0);
    }
}
