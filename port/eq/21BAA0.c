#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023F420(s32 arg0);
s32 func_001FA1D0(s32 arg0, f32 farg0);
s32 func_002174B8(s32 arg0);
s32 func_00210E18(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_0023C710(s32 arg0);

extern f32 D_00385CC8;
extern f32 D_00385CCC;
extern f32 D_00385CD0;
extern f32 D_00385CD4;

s32 func_0021BAA0(u8 *arg0) {
    s32 v3;

    if (func_00211310((s32)arg0, 4, 2) != 0) {
        if (BtlPad_Test4C((s32)arg0, 0) != 0) {
            func_002174D8((s32)arg0, 0x49);
        }
        if ((*(s32 *)(arg0 + 0x9A0) > 0) || (func_00211310((s32)arg0, 0, 0x800) != 0)) {
            if ((func_0023F420((s32)arg0) & 0x80) != 0) {
                if ((BtlPad_Test4C((s32)arg0, 3) != 0) && (*(s32 *)(arg0 + 0x9A0) < *(s32 *)(arg0 + 0x9A4))) {
                    func_002174D8((s32)arg0, 0x10);
                }
            }
            if (BtlPad_Test48((s32)arg0, 7) == 0) {
                BtlPad_Test4C((s32)arg0, 2);
                if (((func_0023F420((s32)arg0) & 0x10) != 0) && (BtlPad_Test4C((s32)arg0, 1) != 0) &&
                    (*(s32 *)(arg0 + 0x9A8) < *(s32 *)(arg0 + 0x9AC))) {
                    func_002174D8((s32)arg0, 0x70);
                }
            }
        }
        if (func_001FA1D0((s32)arg0, D_00385CC8) == 0) {
            goto block_33;
        }
        v3 = func_002174B8((s32)arg0);
        if (v3 == -1) {
            goto block_33;
        }
        if ((v3 == 16) || (v3 == 112)) {
            if (func_00210E18((s32)arg0) != 0x99) {
                goto block_33;
            }
            BtlAnim_SetBlend((s32)arg0, D_00385CCC);
            return func_002174B8((s32)arg0);
        }
        BtlAnim_SetBlend((s32)arg0, D_00385CD0);
        return func_002174B8((s32)arg0);
    }

block_33:
    if (func_00211310((s32)arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend((s32)arg0, D_00385CD4);
    return func_0023C710((s32)arg0);
}
