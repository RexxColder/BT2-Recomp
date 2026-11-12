#include "common.h"

void func_00260068(s32 arg0);
s32 func_00261060(s32 arg0, s64 arg1);
void func_00262330(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern s32 D_003B2654 __attribute__((section(".data")));

void func_00261108(s32 arg0, s32 arg1) {
    s32 s0 = arg1 & 0xFFFF;

    if ((D_003B2654 & 0x100) == 0) {
        s64 a1;

        func_00262330(1, s0, arg0 & 0xFFFF);
        a1 = (s64)0x8000 << 20;
        if ((*(s64 *)(D_003876A0 + 0x4D8) & a1) == 0) {
            func_00260068(func_00261060(s0, a1));
        }
    }
}
