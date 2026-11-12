#include "common.h"

s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00386B10;

s32 func_00238DB0(s32 arg0) {
    if (func_001FA288(arg0, 0x190) == 0) {
        if (func_001FA288(arg0, 0x1B0) == 0) {
            return -1;
        }
    }
    BtlAnim_SetBlend(arg0, D_00386B10);
    return func_0023C710(arg0);
}
