#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C3210(s32 arg0);
void func_002CCB08(s32 arg0, s32 arg1, s32 arg2);

void func_002CCA78(u8 *arg0, s32 arg1) {
    s32 temp;
    s32 a2;

    if (func_002C3210((s32)arg0) != 0) {
        func_002C2FF0(0, (s32)0xFF000142, 1);
        return;
    }
    temp = *(s32 *)(arg0 + 0x50);
    a2 = (temp != 0) ? 2 : 1;
    if (arg1 != 0 || (a2 = 0, temp != 0)) {
        *(s32 *)(arg0 + 0x50) = arg1;
        func_002CCB08((s32)arg0, a2, a2);
        *(s32 *)(arg0 + 0x44) = 1;
    }
}
