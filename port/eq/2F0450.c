#include "common.h"

/* 0x002F0450: func_002F0178(a0); *(u8 *)(a0 + 1) = 1. */
void func_002F0178(s32 arg0);

void func_002F0450(void *a0) {
    func_002F0178((s32)a0);
    *(u8 *)((u8 *)a0 + 1) = 1;
}
