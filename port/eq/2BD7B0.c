#include "common.h"

s32 strncmp(void *a, void *b, u32 n);
extern u8 D_0037A038[] __attribute__((section(".data")));

s32 func_002BD7B0(u8 *arg0, s32 arg1, s32 *arg2) {
    s32 ret;

    *arg2 = 0x120;
    ret = 0;
    if (arg1 >= 0x120 && arg0[0] == 0x80 && arg0[1] == 0) {
        ret = strncmp(arg0 + 0x11A, D_0037A038, 6) == 0;
    }
    return ret;
}
