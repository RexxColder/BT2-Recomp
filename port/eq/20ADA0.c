#include "common.h"

/* GUESS arity: a0 is passed through to func_00211288 (not written before the call) */
s32 func_00211288(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_0020ADA0(u32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    if (D_00387930 != 0 && arg0 < 2U) {
        temp_v0 = func_00211288((s32)arg0);
        temp_v0_2 = BtlObjXf_Update(temp_v0);
        if (temp_v0_2 == 0x19C) {
            return 1;
        }
        if (temp_v0_2 < 0x19D) {
            return (temp_v0_2 == 0x19A) ? 1 : 0;
        }
        if (temp_v0_2 != 0x19D) {
            return 0;
        }
        if (func_00211310(temp_v0, 2, 1) == 0) {
            return 0;
        }
        return 1;
    }
    return 0;
}
