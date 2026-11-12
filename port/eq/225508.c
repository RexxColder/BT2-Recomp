#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlObjXf_Update(f32 farg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023BDA8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_003861CC;
extern f32 D_003861D0;

s32 func_00225508(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_0023BDA8(arg0, 0x71E);
    if (temp_v0 != -1) {
        BtlAnim_SetBlend(D_003861CC, arg0);
        return temp_v0;
    }
    temp_v0_2 = BtlObjXf_Update(D_003861CC, arg0);
    if (temp_v0_2 == 0 || temp_v0_2 == 0x32) {
        if (func_00211310(arg0, 2, 0x200) == 0) {
            BtlAnim_SetBlend(D_003861D0, arg0);
            return func_0023C710(arg0);
        }
    }
    return -1;
}
