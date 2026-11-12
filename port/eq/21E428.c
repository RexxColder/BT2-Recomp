#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void BtlAnim_SetBlend(f32 arg0, s32 arg1);
void *BtlMember_GetActiveGauge(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_002174B8(s32 arg0);
s32 func_0023C710(s32 arg0);
extern f32 D_00385E64;
extern f32 D_00385E68;
extern f32 D_00385E6C;
extern f32 D_00385E70;

s32 func_0021E428(s32 arg0) {
    s32 temp_v0;

    if (func_00211310(arg0, 0, 0x800) != 0) {
        if (BtlPad_Test4C(arg0, 0) != 0) {
            func_002174D8(arg0, 0x6F);
        }
        if (BtlPad_Test4C(arg0, 1) != 0) {
            func_002174D8(arg0, 0x5D);
        }
    }
    temp_v0 = BtlObjXf_Update(arg0);
    if ((temp_v0 != 0) && (temp_v0 != 0x32)) {
        if (func_00211310(arg0, 2, 1) != 0) {
            if ((func_00211310(arg0, 4, 2) != 0) && (func_002174B8(arg0) != -1)) {
                BtlAnim_SetBlend(D_00385E64, arg0);
                return func_002174B8(arg0);
            }
            BtlAnim_SetBlend(D_00385E68, arg0);
            *(s32 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x1C) = 0;
            *(s32 *)((u8 *)arg0 + 0xA34) = 0x3C;
            return func_0023C710(arg0);
        }
        return -1;
    }
    if (func_00211310(arg0, 4, 2) == 0) {
        goto block_22;
    }
    if (func_002174B8(arg0) == -1) {
block_22:
        if (func_00211310(arg0, 2, 0x200) == 0) {
            BtlAnim_SetBlend(D_00385E70, arg0);
            *(s32 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x1C) = 0;
            *(s32 *)((u8 *)arg0 + 0xA34) = 0x3C;
            return func_0023C710(arg0);
        }
        return -1;
    }
    BtlAnim_SetBlend(D_00385E6C, arg0);
    return func_002174B8(arg0);
}
