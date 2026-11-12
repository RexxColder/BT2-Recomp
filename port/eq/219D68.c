#include "common.h"

extern f32 D_00385BE4;
extern f32 D_00385BE8;
extern f32 D_00385BEC;

s32 BtlObjXf_Update(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00210E18(u8 *arg0);
s32 func_0023F420(u8 *arg0);
s32 BtlPad_Test4C(u8 *arg0, s32 arg1);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
void func_002174D8(u8 *arg0, s32 arg1);
s32 func_001FA1D0(u8 *arg0, f32 farg0);
s32 func_002174B8(u8 *arg0);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);
s32 func_0023C710(u8 *arg0);

s32 func_00219D68(u8 *arg0) {
    s32 v;
    s32 idx;

    v = BtlObjXf_Update(arg0);
    idx = v - 0x58;
    if ((u32)idx >= 0x10 || (idx % 3) != 0) {
        return -1;
    }

    if (func_00211310(arg0, 4, 2) != 0 && func_00210E18(arg0) == 0x99) {
        if (func_0023F420(arg0) & 0x80) {
            if (BtlPad_Test4C(arg0, 3) != 0) {
                func_002174D8(arg0, 0x10);
            }
        }
        if (BtlPad_Test48(arg0, 7) == 0) {
            BtlPad_Test4C(arg0, 2);
            if (func_0023F420(arg0) & 0x10) {
                if (BtlPad_Test4C(arg0, 1) != 0) {
                    func_002174D8(arg0, 0x70);
                }
            }
        }
        if (func_001FA1D0(arg0, D_00385BE4) != 0) {
            v = func_002174B8(arg0);
            if (v == 0x70 || (v < 0x71 ? (v == 0x10) : (v == 0x8D))) {
                BtlAnim_SetBlend(arg0, D_00385BE8);
                return func_002174B8(arg0);
            }
        }
    }

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00385BEC);
    return func_0023C710(arg0);
}
