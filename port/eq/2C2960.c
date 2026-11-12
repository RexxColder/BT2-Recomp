#include "common.h"

s32 func_002C2CC0(s32 arg0, void *arg1);
extern u8 func_002D4E18[] __attribute__((section(".data")));
extern u8 func_002D4E68[] __attribute__((section(".data")));
extern u8 func_002D4EB8[] __attribute__((section(".data")));
extern u8 func_002D4F08[] __attribute__((section(".data")));
extern u8 func_002D4FC0[] __attribute__((section(".data")));
extern u8 func_002D5010[] __attribute__((section(".data")));
extern u8 func_002D5060[] __attribute__((section(".data")));

void func_002C2960(s32 arg0, s32 *arg1) {
    arg1[0] = func_002C2CC0(arg0, func_002D4E18);
    arg1[1] = func_002C2CC0(arg0, func_002D4E68);
    arg1[2] = func_002C2CC0(arg0, func_002D4EB8);
    arg1[3] = func_002C2CC0(arg0, func_002D4F08);
    arg1[4] = func_002C2CC0(arg0, func_002D4FC0);
    arg1[5] = func_002C2CC0(arg0, func_002D5010);
    arg1[6] = func_002C2CC0(arg0, func_002D5060);
}
