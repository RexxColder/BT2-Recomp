#include "common.h"

extern void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_00355338[] __attribute__((section(".data")));

/* 0x002FB520: clears the 0x38 bytes at D_00355338 (the original also loads a word from D_00355370 that is unused). */
void func_002FB520(void) {
    memset(D_00355338, 0, 0x38);
}
