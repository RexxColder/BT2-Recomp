#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002D4630(u8 *arg0);

/* 0x002D49B0(obj, out): out[0] = 0; s1 = obj->+4 + 0x60 (taken before the call); when func_002D4630(obj) is nonzero:
 * clear 0x21 bytes of out and copy 0x20 bytes from s1 to out. */
void func_002D49B0(u8 *arg0, u8 *arg1) {
    u8 *s1;

    arg1[0] = 0;
    s1 = *(u8 **)(arg0 + 4) + 0x60;
    if (func_002D4630(arg0) == 0) {
        return;
    }
    memset(arg1, 0, 0x21);
    memcpy(arg1, s1, 0x20);
}
