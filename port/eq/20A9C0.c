#include "common.h"

/* 0x0020A9C0: if (!D_00387930 || (u32)a0 >= 2) return 0; v = BtlObjXf_Update(func_00211288(a0)); return v >= 0x11A && v < 0x11C. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);

s32 func_0020A9C0(s32 a0) {
    s32 v;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    v = BtlObjXf_Update(func_00211288(a0));
    return v >= 0x11A && v < 0x11C;
}
