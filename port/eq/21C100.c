#include "common.h"

void BtlAnim_SetBlend(f32 farg0, void *arg1);
s32 BtlObjXf_Update(void *arg0);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
f32 func_001FA318(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_002174B8(void *arg0);
void func_002174D8(void *arg0, s32 arg1);
s32 func_0023C710(void *arg0);
s32 func_0023C798(void *arg0, s32 arg1);
s32 func_0023F420(void *arg0);
extern f32 D_00385CFC;
extern f32 D_00385D00;
extern f32 D_00385D04;
extern f32 D_00385D08;
extern f32 D_00385D0C;
extern f32 D_00385D10;

s32 func_0021C100(void *arg0) {
    s32 temp_v0;

    if (func_00211310(arg0, 4, 2) != 0) {
        if (BtlPad_Test4C(arg0, 0) != 0) {
            func_002174D8(arg0, 0x49);
        }
        if ((func_0023F420(arg0) & 0x10000) && (BtlPad_Test4C(arg0, 1) != 0)) {
            func_002174D8(arg0, 0x76);
        }
        temp_v0 = func_002174B8(arg0);
        if (temp_v0 != -1) {
            if (temp_v0 == 0x76) {
                if ((D_00385CFC < func_001FA318(arg0)) && (func_001FA318(arg0) < D_00385D00)) {
                    BtlAnim_SetBlend(D_00385D04, arg0);
                    return func_002174B8(arg0);
                }
                goto block_15;
            }
            if (D_00385D08 < func_001FA318(arg0)) {
                BtlAnim_SetBlend(D_00385D0C, arg0);
                return func_002174B8(arg0);
            }
        }
    }
block_15:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385D10, arg0);
    if ((BtlObjXf_Update(arg0) == 0x39) && (*(s32 *)((u8 *)arg0 + 0x9C0) >= 0)) {
        temp_v0 = func_0023C798(arg0, 0x200);
        if (temp_v0 == -1) {
            return func_0023C710(arg0);
        }
        return temp_v0;
    }
    return func_0023C710(arg0);
}
