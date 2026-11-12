#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00386344;

s32 func_00227A18(s32 arg0) {
    if (func_001FA288(arg0, 0x19) != 0) {
        BtlAnim_SetBlend(arg0, D_00386344);
        return func_0023C710(arg0);
    }
    return -1;
}
