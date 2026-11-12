#include "common.h"

void *memset(void *dst, s32 c, u32 n);
extern s32 D_00364B00 __attribute__((section(".data")));
extern u8 D_00364B08[] __attribute__((section(".data")));

/* 0x00305440 func_00305440: Init con contador: si D_00364B00 == 0 limpia D_00364B08 (0xC00 bytes); siempre D_00364B00++. */
void func_00305440(void) {
    if (D_00364B00 == 0) {
        memset(D_00364B08, 0, 0xC00);
    }
    D_00364B00 += 1;
}
