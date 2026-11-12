#include "common.h"

s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_0020BCA0(u32 arg0) {
    s32 temp_v0;

    if ((D_00387930 == 0) || (arg0 >= 2U)) {
        return 0;
    }
    temp_v0 = func_00211288((s32)arg0);
    if (BtlMember_IsHealthEmpty_2127F8(temp_v0) != 0) {
        return 0;
    }
    if (func_00211310(temp_v0, 0xF, 0x10) == 0) {
        return 0;
    }
    return 1;
}
