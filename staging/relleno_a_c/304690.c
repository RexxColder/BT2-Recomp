#include "common.h"

void *memset(void *dst, s32 c, u32 n);
extern s32 D_00360AC8 __attribute__((section(".data")));
extern u8 D_00360AD0[] __attribute__((section(".data")));

/* 0x00304690 func_00304690: Init con contador: si D_00360AC8 == 0 limpia D_00360AD0 (0x4000 bytes); siempre D_00360AC8++. */
void func_00304690(void) {
    if (D_00360AC8 == 0) {
        memset(D_00360AD0, 0, 0x4000);
    }
    D_00360AC8 += 1;
}
