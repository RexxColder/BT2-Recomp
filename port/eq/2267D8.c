#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
extern f32 D_0038627C;

s32 func_002267D8(s32 arg0) {
    if (func_001FA288(arg0, 0x89) != 0) {
        BtlAnim_SetBlend(arg0, D_0038627C);
        return func_0023C710(arg0);
    }
    return -1;
}
