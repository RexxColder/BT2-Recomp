#include "common.h"

void func_001AD0E0(u8 *arg0, s32 arg1, s32 arg2);
void func_001AD418(u8 *arg0, s32 arg1);

void func_001AC748(u8 *arg0, s32 pad, s32 arg2) {
    u8 t = *(u8 *)(*(u8 **)(arg0 + 0x38) + 0x1A);

    if (t == 14) {
        func_001AD418(arg0, t);
        return;
    }
    if (t == 15) {
        func_001AD0E0(arg0, t, arg2);
        return;
    }
}
