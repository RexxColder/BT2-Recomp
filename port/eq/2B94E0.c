#include "common.h"

void BtlObjXf_SetMtx(s32 arg0, s32 arg1);
s32 func_002B9408(s32 arg0);
s32 func_002B95F8(s32 arg0, s32 arg1);

void func_002B94E0(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v0;
    s32 var_s1;

    temp_a1 = *(s32 *)(arg0 + 0x4C);
    if (temp_a1 != 0) {
        var_s1 = temp_a1;
    } else {
        temp_v0 = func_002B95F8(arg0, *(s32 *)(arg1 + 0x30));
        if (temp_v0 != -1) {
            *(s32 *)(arg0 + 0x50) = temp_v0;
        } else {
            *(s32 *)(arg0 + 0x50) = 0x11;
        }
        var_s1 = *(s32 *)(arg0 + 0x50);
    }
    BtlObjXf_SetMtx(func_002B9408(arg0), var_s1);
}
