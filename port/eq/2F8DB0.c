#include "common.h"

/* 0x002F8DB0: stores the halfwords a1, a2, a3 at +0x34, +0x36, +0x38 of a0. */
void func_002F8DB0(void *a0, s16 a1, s16 a2, s16 a3) {
    *(s16 *)((u8 *)a0 + 0x34) = a1;
    *(s16 *)((u8 *)a0 + 0x36) = a2;
    *(s16 *)((u8 *)a0 + 0x38) = a3;
}
