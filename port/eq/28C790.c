#include "common.h"

void func_0028C790(void) {
    while ((u32)*(volatile u32 *)0x10000800 < 0x190U) {
    }
    *(volatile u32 *)0x10000810 &= ~0x80U;
    *(volatile u32 *)0x10000800 = 0;
}
