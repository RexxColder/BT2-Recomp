#include "common.h"

void LipSync_Clear(s32 arg0);
void *memset(void *s, s32 c, u32 n);
extern u8 gColorFade[] __attribute__((section(".data")));

void func_00243968(s32 arg0, s32 arg1, s32 arg2) {
    memset(gColorFade, 0, 0x18);
    *(s32 *)(gColorFade + 0x04) = arg0;
    *(s32 *)(gColorFade + 0x08) = arg1;
    *(s32 *)(gColorFade + 0x0C) = arg2;
    *(s32 *)(gColorFade + 0x14) = 6;
    *(s32 *)(gColorFade + 0x00) = 1;
    *(s32 *)(gColorFade + 0x10) = 0x80;
    LipSync_Clear(0x80);
}
