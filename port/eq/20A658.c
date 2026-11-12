#include "common.h"

/* 0x0020A658: if (!D_00387930 || (u32)a0 >= 2) return 0; return func_00211288(a0)->+0x984 > 0. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);

s32 func_0020A658(s32 a0) {
    u8 *p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = (u8 *)func_00211288(a0);
    return *(s32 *)(p + 0x984) > 0;
}
