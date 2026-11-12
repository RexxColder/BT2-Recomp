#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023F420(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
extern f32 D_003865C4;
extern f32 D_003865C8;

s32 func_0022C450(s32 arg0) {
    if (BtlObjXf_Update(arg0) == 0x38 && BtlPad_Test48(arg0, 5) == 0) {
        BtlAnim_SetBlend(arg0, D_003865C4);
        return func_0023C710(arg0);
    }
    if (BtlObjXf_Update(arg0) != 0x39 || !(func_0023F420(arg0) & 0x80000) || BtlPad_Test4C(arg0, 1) == 0) {
        if (func_001FA288(arg0, 0x39) == 0) {
            return -1;
        }
        BtlAnim_SetBlend(arg0, D_003865C8);
        return func_0023C710(arg0);
    }
    return 0x57;
}
