#include "common.h"

/* 0x0020AC98: if (!D_00387930 || (u32)a0 >= 2) return 0; p = func_00211288(a0);
   if (func_0023F410(p) & 0x10) return 0; if (func_00217488(p) != 0x2D) return 0; return BtlObjXf_Update(p) == 0x41. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_0023F410(s32 arg0);
s32 func_00217488(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);

s32 func_0020AC98(s32 a0) {
    s32 p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = func_00211288(a0);
    if (func_0023F410(p) & 0x10) {
        return 0;
    }
    if (func_00217488(p) != 0x2D) {
        return 0;
    }
    return BtlObjXf_Update(p) == 0x41;
}
