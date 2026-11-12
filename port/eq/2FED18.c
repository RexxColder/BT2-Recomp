#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
s32 strcmp(void *arg0, void *arg1);
extern u8 D_0037E668[] __attribute__((section(".data")));

s32 func_002FED18(void *arg0) {
    u8 sp[16];
    s32 i;

    memset(sp, 0, 6);
    for (i = 0; i < 4; i++) {
        sp[i] = ((u8 *)arg0)[i];
    }
    sp[5] = 0;
    return strcmp(sp, D_0037E668) == 0;
}
