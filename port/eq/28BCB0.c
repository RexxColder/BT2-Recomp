#include "common.h"

extern s32 D_00387EB4;
extern u8 D_0038A638[] __attribute__((section(".data")));

/* 0x0028BCB0: copies the 8-byte entry at index D_00387EB4 of D_0038A638 to the next entry, then advances the index. */
void func_0028BCB0(void) {
    s32 idx = D_00387EB4;

    *(s64 *)(D_0038A638 + idx * 8 + 8) = *(s64 *)(D_0038A638 + idx * 8);
    D_00387EB4 = idx + 1;
}
