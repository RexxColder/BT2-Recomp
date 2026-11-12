#include "common.h"

/* 0x0026C770: p = *(a0 + 8); if (p) tail func_0026DF68(p + 0xA8, a1, 1). */
void func_0026DF68(s32 arg0, s32 arg1, s32 arg2);

void func_0026C770(void *a0, s32 a1) {
    u8 *p;

    p = *(u8 **)((u8 *)a0 + 8);
    if (p != NULL) {
        func_0026DF68((s32)(p + 0xA8), a1, 1);
    }
}
