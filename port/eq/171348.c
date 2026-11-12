#include "common.h"

extern f32 D_003848C0 __attribute__((section(".data")));

void func_00171348(void *arg0) {
    u8 *p;

    p = *(u8 **)((u8 *)arg0 + 0xB0);
    if (**(s32 **)(p + 0x20) == 0x174) {
        *(f32 *)((u8 *)arg0 + 0x10) = *(f32 *)((u8 *)arg0 + 0x10) * D_003848C0;
    }
}
