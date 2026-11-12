#include "common.h"

s32 func_00211288(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
extern s32 D_00387930;

/* 1 when D_00387930 is set, arg0 < 2 and r = BtlObjXf_Update(func_00211288(arg0)) is in [0x11A, 0x11C); 0 otherwise */
s32 func_0020A9C0(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        s32 r = BtlObjXf_Update(func_00211288(arg0));
        if (r < 0x11C) {
            if (r >= 0x11A) {
                return 1;
            }
        }
    }
    return 0;
}
