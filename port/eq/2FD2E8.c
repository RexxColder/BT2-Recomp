#include "common.h"

extern void (*D_00356004)(s32, s32, s32) __attribute__((section(".data")));
extern s32 D_00356008 __attribute__((section(".data")));

void func_002FD2E8(s32 arg0, s32 arg1) {
    if (D_00356004 != NULL) {
        D_00356004(D_00356008, arg1, arg0);
    }
}
