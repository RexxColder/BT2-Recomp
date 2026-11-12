#include "common.h"

s32 func_002C2FF0(u8 *arg0, s32 arg1);
s32 func_002C3210(u8 *arg0);
void func_002D03C8(u8 *arg0, s32 arg1);

s32 func_002D00C8(u8 *arg0, s32 arg1) {
    s32 v0 = func_002C3210(arg0);
    u8 *v1;

    if (v0 != 0) {
        return func_002C2FF0(NULL, (s32)0xFF000159);
    }
    v1 = *(u8 **)(arg0 + 0x36B0);
    if (v1 != NULL) {
        *(s32 *)(v1 + 0xDC4) = arg1;
        func_002D03C8(arg0, (s32)0xFF000000);
        v0 = 0;
    }
    return v0;
}
