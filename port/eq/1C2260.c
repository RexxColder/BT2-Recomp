#include "common.h"

void func_001C2158(s32 a0, s32 a1);

/* 0x001C2260 (approx): clear 0xF0 bytes at a0, then func_001C2158(a0, 1). */
void func_001C2260(u8 *a0) {
    __builtin_memset(a0, 0, 0xF0);
    func_001C2158((s32)a0, 1);
}
