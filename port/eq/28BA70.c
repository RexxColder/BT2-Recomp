#include "common.h"

s32 malloc(s32 arg0);
void free(s32 arg0);
extern s32 D_00387D48 __attribute__((section(".data")));
extern u8 D_43058F[] __attribute__((section(".data")));

void func_0028BA70(void) {
    s32 size = 0x01EFE000 - (s32)D_43058F;

    D_00387D48 = size;
    free(malloc(size - 0x40));
}
