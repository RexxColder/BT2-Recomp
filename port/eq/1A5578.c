#include "common.h"

extern u8 *D_00387830;

/* 0x001A5578: a delay count (18 rounds, no visible effect), then clears the word at +0x69C and the word at +0x10C of
 * D_00387830. */
void func_001A5578(void) {
    s32 v0 = 0x12;

    do {
        v0 -= 1;
    } while (v0 >= 0);
    *(s32 *)(D_00387830 + 0x340 + 0x35C) = 0;
    *(s32 *)(D_00387830 + 0x10C) = 0;
}
