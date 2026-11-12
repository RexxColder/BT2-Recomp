#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0, s32 arg1);
extern s32 D_0037A530[] __attribute__((section(".data")));

void func_002D2128(s32 arg0, s32 *arg1) {
    s32 v1;

    *arg1 = -1;
    if (func_002C3210(arg0, (s32)arg1) != 0) {
        func_002C2FF0(0, 0xFF00011B);
        return;
    }
    v1 = *(s32 *)(arg0 + 0x920);
    if (v1 != 0) {
        *arg1 = D_0037A530[v1];
    }
}
