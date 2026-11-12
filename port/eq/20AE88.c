#include "common.h"

/* 0x0020AE88: if (!D_00387930 || (u32)a0 >= 2) return 0; p = func_00211288(a0); flag = 1;
   for (i = 0; i < p->+0x1184; i++) { q = func_00202E60(p, i); if (*(s32 *)q > 0) { flag = 0; break; } } return flag. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_00202E60(s32 arg0, s32 arg1);

s32 func_0020AE88(s32 a0) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 flag;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = (u8 *)func_00211288(a0);
    flag = 1;
    for (i = 0; i < *(s32 *)(p + 0x1184); i++) {
        q = (u8 *)func_00202E60((s32)p, i);
        if (*(s32 *)q > 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}
