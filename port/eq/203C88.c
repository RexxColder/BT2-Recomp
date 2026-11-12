#include "common.h"

u8 *func_00202DC0(s32 a0);

/* 0x00203C88: clear bits a1 in the s64 at +0x28 of func_00202DC0(a0). */
void func_00203C88(s32 a0, s64 a1) {
    u8 *p = func_00202DC0(a0);
    *(s64 *)(p + 0x28) &= ~a1;
}
