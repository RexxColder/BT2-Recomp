#include "common.h"

extern s32 D_00345338 __attribute__((section(".data")));
extern s32 D_0034533C __attribute__((section(".data")));
extern s32 D_0038BAF0[] __attribute__((section(".data")));

void func_002B3140(s32 arg0, s32 arg1, s32 *arg2) {
    s32 i;

    D_00345338 = arg0;
    D_0034533C = arg1;
    for (i = 0; i < arg0; i++) {
        D_0038BAF0[i] = arg2[i];
    }
}
