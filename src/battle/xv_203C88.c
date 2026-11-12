#include "common.h"

s32 func_00202DC0(s32 arg0);

/* clears the bits of mask arg1 in the 64-bit word at +0x28 of obj = func_00202DC0(arg0) */
void func_00203C88(s32 arg0, s64 arg1) {
    s64 *obj = (s64 *)func_00202DC0(arg0);
    obj[5] &= ~arg1;
}
