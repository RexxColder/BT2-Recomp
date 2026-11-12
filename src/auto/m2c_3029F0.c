#include "m2c_macros.h"

extern s16 D_0035D27C __attribute__((section(".data")));
extern s16 D_0035D27E __attribute__((section(".data")));

void func_003029F0(s16 arg0, s16 arg1) {
    D_0035D27C = arg0;
    D_0035D27E = arg1;
}
