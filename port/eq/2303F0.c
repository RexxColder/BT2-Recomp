#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
void func_00212890(s32 arg0);
s32 func_0023C710(s32 arg0);
extern f32 D_0038681C;
extern f32 D_00386820;

s32 func_002303F0(f32 farg0, s32 arg0) {
    if (func_00211310(farg0, arg0, 7, 0x2000) != 0) {
        BtlAnim_SetBlend(D_0038681C, arg0, 7, 0x1000);
        func_00212890(0x78);
        return func_0023C710(arg0);
    }
    if (func_00211310(D_0038681C, arg0, 7, 0x1000) != 0) {
        /* a1/a2 are not rewritten after the second call: the values set before it are reused */
        BtlAnim_SetBlend(D_00386820, arg0, 7, 0x1000);
        return 0xE3;
    }
    return -1;
}
