#include "common.h"

/* 0x0026F888: memset(a0, 0, 0x38); *(s32 *)a0 = 0. */
void func_0026F888(void *a0) {
    memset(a0, 0, 0x38);
    *(s32 *)a0 = 0;
}
