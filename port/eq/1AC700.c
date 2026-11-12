#include "common.h"

s32 func_001ACD88(u8 *arg0, s32 arg1, s32 arg2);
void func_001AD318(u8 *arg0, s32 arg1);

void func_001AC700(u8 *arg0, s32 pad, s32 arg2) {
    u8 t = *(u8 *)(*(u8 **)(arg0 + 0x38) + 0x1A);

    if (t == 14) {
        func_001AD318(arg0, t);
        return;
    }
    if (t == 15) {
        func_001ACD88(arg0, t, arg2);
        return;
    }
}
