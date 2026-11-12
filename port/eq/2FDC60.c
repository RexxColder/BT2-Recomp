#include "common.h"

extern void func_002FD2E8(u8 *arg0, u8 *arg1);
extern u8 D_0037E428[] __attribute__((section(".data")));

/* 0x002FDC60: signed byte at +2 of arg0; for arg0 == NULL, calls func_002FD2E8(NULL, D_0037E428) and returns 0. */
s32 func_002FDC60(u8 *arg0) {
    if (arg0 == NULL) {
        func_002FD2E8(arg0, D_0037E428);
        return 0;
    }
    return *(s8 *)(arg0 + 2);
}
