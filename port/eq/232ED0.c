#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212320(s32 arg0);
s32 func_0023C710(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002411E0(s32 arg0, s32 arg1);
extern f32 D_003868F4;

s32 func_00232ED0(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(D_003868F4, arg0);
        if (func_002411E0(arg0, func_00212320(arg0)) & 0x200000) {
            func_002113C0(arg0, 1, 0x40000, 1);
            func_002113C0(arg0, 1, 0x80000, 1);
            func_002113C0(arg0, 2, 0x1000, 1);
            return 0x21;
        }
        return func_0023C710(arg0, 1, 0x40000, 1);
    }
    return -1;
}
