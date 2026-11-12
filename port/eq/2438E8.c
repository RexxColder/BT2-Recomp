#include "common.h"

extern u8 gColorFade[] __attribute__((section(".data")));

void func_002438E8(void) {
    if ((*(s32 *)(gColorFade + 0x00) & 1) != 0) {
        if (*(s32 *)(gColorFade + 0x10) > 0) {
            *(s32 *)(gColorFade + 0x10) = *(s32 *)(gColorFade + 0x10) - *(s32 *)(gColorFade + 0x14);
        } else {
            *(s32 *)(gColorFade + 0x00) = 4;
        }
    }
    if ((*(s32 *)(gColorFade + 0x00) & 2) != 0) {
        if (*(s32 *)(gColorFade + 0x10) >= *(s32 *)(gColorFade + 0x14) + 0x80) {
            *(s32 *)(gColorFade + 0x00) = 8;
        } else {
            *(s32 *)(gColorFade + 0x10) = *(s32 *)(gColorFade + 0x10) + *(s32 *)(gColorFade + 0x14);
        }
    }
}
