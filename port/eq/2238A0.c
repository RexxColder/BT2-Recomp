#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023C780(s32 arg0);
extern f32 D_003860E4;

s32 func_002238A0(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, D_003860E4);
        func_002113C0(arg0, 0, 2, 0);
        if (func_00211310(arg0, 0, 4) != 0) {
            return func_0023C780(arg0);
        }
        return 0x21;
    }
    return -1;
}
