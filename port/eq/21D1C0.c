#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
s32 func_00210E18(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
s32 func_0023F420(s32 arg0);
extern f32 D_00385DBC;
extern f32 D_00385DC0;

s32 func_0021D1C0(u8 *arg0) {
    s32 temp_v0;
    s32 a0 = (s32)arg0;

    if (func_00211310(a0, 4, 0x1002) != 0) {
        if (!(func_0023F420(a0) & 0x40000)) {
            goto block_14;
        }
        if ((func_00210E18(a0) == 0x9A) && (BtlPad_Test4C(a0, 1) != 0) && (BtlPad_Test48(a0, 7) == 0)) {
            func_002174D8(a0, 0x6B);
        }
        if (!(D_00385DBC < func_001FA318(a0))) {
            goto block_14;
        }
        if (func_002174B8(a0) == 0x6B) {
            return func_002174B8(a0);
        }
block_14:
        if (BtlPad_Test4C(a0, 0) != 0) {
            func_002174D8(a0, 0x49);
        }
        goto block_16;
    }
block_16:
    if (func_00211310(a0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385DC0, a0);
    if ((BtlObjXf_Update(a0) != 0x39) || (*(s32 *)(arg0 + 0x9C0) < 0) ||
        (temp_v0 = func_0023C798(a0, 0x200), (temp_v0 == -1))) {
        if (func_002174B8(a0) != -1) {
            return func_002174B8(a0);
        }
        return func_0023C710(a0);
    }
    return temp_v0;
}
