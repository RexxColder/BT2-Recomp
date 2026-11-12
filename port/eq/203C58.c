#include "common.h"

/* 0x00203C58: p = func_00202DC0(a0); return (*(s64 *)(p + 0x28) & a1) != 0. */
s32 func_00202DC0(s32 arg0);

s32 func_00203C58(s32 a0, s64 a1) {
    u8 *p;
    s64 m;

    p = (u8 *)func_00202DC0(a0);
    m = *(s64 *)(p + 0x28) & (s64)a1;
    return m != 0;
}
