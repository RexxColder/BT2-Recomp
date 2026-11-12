#include "common.h"

/* 0x00101F18: obj = func_00101A88(a0); *a1 = (obj byte 0x1C5 != 1); *a2 = obj word 0x10; returns obj. */
s32 func_00101A88(s32 arg0);

s32 func_00101F18(s32 a0, u8 *a1, s32 *a2) {
    u8 *obj;

    obj = (u8 *)func_00101A88(a0);
    *a1 = (obj[0x1C5] != 1);
    *a2 = *(s32 *)(obj + 0x10);
    return (s32)obj;
}
