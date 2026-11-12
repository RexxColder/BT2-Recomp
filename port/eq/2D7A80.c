#include "common.h"

s32 func_002D7AE8(f32 arg0, f32 arg1);
void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037ACF0[] __attribute__((section(".data")));

void func_002D7A80(s32 arg0, f32 farg0, f32 farg1) {
    if (func_002D7AE8(farg0, farg1) != 1) {
        func_002D6C90(0, 0, (s32)D_0037ACF0);
    }
    *(f32 *)((u8 *)arg0 + 0x3C) = farg0;
    *(f32 *)((u8 *)arg0 + 0x40) = farg1;
}
