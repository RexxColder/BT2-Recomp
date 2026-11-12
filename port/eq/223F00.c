#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1, s32 arg2);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test48(f32 farg0, s32 arg1, s32 arg2);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023BDA8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00386118;
extern f32 D_0038611C;
extern f32 D_00386120;

s32 func_00223F00(s32 arg0) {
    s32 temp_v0;

    if ((BtlObjXf_Update(arg0) != 0x42) && (func_00211310(arg0, 0, 0x800) == 0)) {
        temp_v0 = func_0023BDA8(arg0, 0x063407C2);
        if (temp_v0 != -1) {
            BtlAnim_SetBlend(D_00386118, arg0, 7);
            return temp_v0;
        }
        if (BtlPad_Test48(D_00386118, arg0, 7) == 0) {
            BtlAnim_SetBlend(D_0038611C, arg0, 0);
            return func_0023C710(arg0);
        }
        goto block_8;
    }
block_8:
    if (func_001FA288(arg0, 0x42) != 0) {
        BtlAnim_SetBlend(D_00386120, arg0, 0);
        return func_0023C710(arg0);
    }
    return -1;
}
