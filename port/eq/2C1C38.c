#include "common.h"

s32 BtlCharApi_GetOpponentObjId(s32 arg0);
s32 func_002DA928(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002DCE00(s32 arg0);

s32 func_002C1C38(s32 arg0, s32 arg1) {
    s32 sp0;
    s32 sp4;
    s32 temp_s1;
    s32 var_v0;

    temp_s1 = BtlCharApi_GetOpponentObjId(arg0);
    var_v0 = arg0 + ((arg1 < 7) ? arg1 : 6);
    if (temp_s1 != 0) {
        func_002DA928(temp_s1, arg0, arg1, (s32)&sp0, (s32)&sp4);
        func_002DCE00(temp_s1);
        var_v0 = arg0 + sp0;
    }
    return var_v0;
}
