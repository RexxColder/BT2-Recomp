#include "common.h"

void LipSync_Clear(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 gColorFade[] __attribute__((section(".data")));

void func_002439E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 lo;

    memset(gColorFade, 0, 0x18);
    lo = 0x80 / arg3;
    *(s32 *)(gColorFade + 0x0) = 1;
    *(s32 *)(gColorFade + 0x4) = arg0;
    *(s32 *)(gColorFade + 0x8) = arg1;
    *(s32 *)(gColorFade + 0xC) = arg2;
    *(s32 *)(gColorFade + 0x10) = 0x80;
    *(s32 *)(gColorFade + 0x14) = lo;
    LipSync_Clear(lo);
}
