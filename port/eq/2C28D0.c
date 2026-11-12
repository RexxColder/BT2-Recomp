#include "common.h"

s32 func_002C2CC0(s32 arg0, s32 arg1);
extern u8 func_002D4BF0[] __attribute__((section(".data")));
extern u8 func_002D4C40[] __attribute__((section(".data")));
extern u8 func_002D4C90[] __attribute__((section(".data")));
extern u8 func_002D4CE0[] __attribute__((section(".data")));

void func_002C28D0(u8 *arg0, u8 *arg1) {
    s32 v;

    *(s32 *)(arg1 + 0x10) = func_002C2CC0((s32)arg0, (s32)func_002D4BF0);
    *(s32 *)(arg1 + 0x14) = func_002C2CC0((s32)arg0, (s32)func_002D4C40);
    v = func_002C2CC0((s32)arg0, (s32)func_002D4C90);
    *(s32 *)(arg1 + 0x18) = v;
    if (v == -1) {
        *(s32 *)(arg1 + 0x18) = 2;
    }
    *(s32 *)(arg1 + 0x1C) = func_002C2CC0((s32)arg0, (s32)func_002D4CE0);
}
