#include "common.h"

extern f32 D_003862AC;
s32 func_001FA288(s32 arg0, s32 arg1);
s32 BtlAnim_SetBlend(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

s32 func_00226CD0(s32 arg0, s32 arg1, s32 arg2) {
    if (func_001FA288(arg0, 0x9B) != 0) {
        BtlAnim_SetBlend(arg0, 0x9B, arg2, D_003862AC);
        return 10;
    }
    return -1;
}
