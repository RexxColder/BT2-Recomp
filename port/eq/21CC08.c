#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlMember_IsKiEmpty(s32 arg0);
void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00385D8C;

s32 func_0021CC08(s32 arg0) {
    s32 s1;
    s32 res;

    if (func_00211310(arg0, 4, 0x10) != 0) {
        res = func_00217488(arg0);
        if (res == 0x66) {
            return 0x69;
        }
        if (res == 0x67) {
            return 0x7E;
        }
    }

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    s1 = 0;
    if (BtlPad_Test48(arg0, 2) == 0 && BtlPad_Test48(arg0, 3) == 0 && BtlPad_Test48(arg0, 1) == 0) {
        s1 = (BtlPad_Test48(arg0, 0) == 0);
    }
    if (BtlMember_IsKiEmpty(arg0) != 0 || s1 != 0) {
        BtlAnim_SetBlend(D_00385D8C, arg0);
        return func_0023C710(arg0);
    }
    return -1;
}
