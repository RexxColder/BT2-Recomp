#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00385C34;
extern f32 D_00385C38;
extern f32 D_00385C3C;
extern f32 D_00385C40;

s32 func_0021AAE0(s32 arg0) {
    s32 temp_v0;

    if (BtlPad_Test4C(arg0, 0) != 0) {
        func_002174D8(arg0, 0x59);
    }
    if (BtlPad_Test4C(arg0, 1) != 0) {
        func_002174D8(arg0, 0x5A);
    }
    temp_v0 = BtlObjXf_Update(arg0);
    if ((temp_v0 == 0x32) || (temp_v0 == 0x0)) {
        if (func_002174B8(arg0) == -1) {
            if (func_00211310(arg0, 2, 0x200) != 0) {
                return -1;
            }
            BtlAnim_SetBlend(D_00385C40, arg0);
            return func_0023C710(arg0);
        }
        BtlAnim_SetBlend(D_00385C3C, arg0);
        return func_002174B8(arg0);
    }
    if (temp_v0 == 0x4C) {
        if (func_00211310(arg0, 2, 1) == 0) {
            return -1;
        }
        BtlAnim_SetBlend(D_00385C38, arg0);
        return func_0023C710(arg0);
    }
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    if (func_002174B8(arg0) == -1) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385C34, arg0);
    return func_002174B8(arg0);
}
