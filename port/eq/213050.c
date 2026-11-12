#include "common.h"

/* 0x00213050: if (func_00211310(a0, 9, 0x4000000) == 0) return 0; r = func_00101720(a0->+0x1534);
   if (r != 3) return r; return func_00101700(a0->+0x1534) (tail, its v0 is returned). */
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00101720(s32 arg0);
s32 func_00101700(s32 arg0);

s32 func_00213050(s32 a0) {
    s32 r;

    if (func_00211310(a0, 9, 0x4000000) == 0) {
        return 0;
    }
    r = func_00101720(*(s32 *)((u8 *)a0 + 0x1534));
    if (r != 3) {
        return r;
    }
    return func_00101700(*(s32 *)((u8 *)a0 + 0x1534));
}
