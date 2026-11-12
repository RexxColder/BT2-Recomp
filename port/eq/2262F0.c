#include "common.h"

s32 BtlAnim_SetBlend(f32 farg0, s32 arg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023BDA8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);

extern f32 D_00386258;
extern f32 D_0038625C;
extern f32 D_00386260;
extern f32 D_00386264;

s32 func_002262F0(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    func_002174D8(arg0, func_0023C798(arg0, 0xC));
    temp_v0_2 = BtlObjXf_Update(arg0);
    if (temp_v0_2 != 0x32) {
        if (temp_v0_2 < 0x33) {
            if (temp_v0_2 != 0) {
                return -1;
            }
            goto block_17;
        }
        if (temp_v0_2 < 0x7F) {
            if (temp_v0_2 < 0x7D) {
                return -1;
            }
            if (func_00211310(arg0, 2, 1) == 0) {
                return -1;
            }
            if (func_002174B8(arg0) == -1) {
                return -1;
            }
            BtlAnim_SetBlend(D_00386258, arg0, 0);
            return func_002174B8(arg0);
        }
        return -1;
    }
block_17:
    temp_v0_3 = func_002174B8(arg0);
    if (temp_v0_3 != -1) {
        BtlAnim_SetBlend(D_0038625C, arg0, 0x20000);
        return func_002174B8(arg0);
    }
    temp_v0 = func_0023BDA8(arg0, 0x207FE);
    if (temp_v0 == temp_v0_3) {
        if (func_00211310(arg0, 2, 0x200) != 0) {
            return -1;
        }
        BtlAnim_SetBlend(D_00386264, arg0, 0);
        return func_0023C710(arg0);
    }
    BtlAnim_SetBlend(D_00386260, arg0, 0);
    return temp_v0;
}
