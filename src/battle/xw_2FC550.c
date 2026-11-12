#include "common.h"

extern s32 D_003553A0 __attribute__((section(".data")));
extern s32 D_003553A4 __attribute__((section(".data")));

// Shifts a two-entry history: the older value (D_003553A0) takes the newer one (D_003553A4), then arg0 is stored
// as the newer one. The barrier keeps the original store order; without it the compiler stores arg0 first.
void func_002FC550(s32 arg0) {
    s32 *old = &D_003553A0;
    s32 *cur = &D_003553A4;
    s32 t = *cur;
    __asm__ volatile("" ::: "memory");
    *old = t;
    *cur = arg0;
}
