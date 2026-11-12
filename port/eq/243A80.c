#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
extern s32 gColorFade[] __attribute__((section(".data")));

void func_00243A80(s32 arg0, s32 arg1, s32 arg2) {
    memset((void *)gColorFade, 0, 0x18);
    gColorFade[1] = arg0;
    gColorFade[2] = arg1;
    gColorFade[3] = arg2;
    gColorFade[0] = 2;
    gColorFade[5] = 6;
    gColorFade[4] = 0;
}
