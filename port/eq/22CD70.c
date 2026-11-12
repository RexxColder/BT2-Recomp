#include "common.h"

void BtlAnim_SetBlend(f32 farg0, u8 *arg1, s32 arg2);
s32 BtlObjXf_Update(u8 *arg0);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
s32 func_001FA288(u8 *arg0, s32 arg1);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0023BDA8(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);
extern f32 D_0038663C;
extern f32 D_00386640;

s32 func_0022CD70(u8 *arg0) {
    s32 var_a1;
    s32 temp_v0;

    if (BtlObjXf_Update(arg0) == 0x3E) {
        temp_v0 = func_0023BDA8(arg0, 0x200);
        if (temp_v0 == -1) {
            goto block_5;
        }
        BtlAnim_SetBlend(D_0038663C, arg0, 0);
        return temp_v0;
    }
block_5:
    if (func_001FA288(arg0, 0x3F) != 0) {
        var_a1 = 1;
        if (*(s32 *)(arg0 + 0x8DC) & 1) {
            var_a1 = 0;
            if (func_00211310(arg0, 1, 1) == 0) {
                if (func_00211310(arg0, 0, 1) == 0) {
                    return 0xF;
                }
                return (BtlPad_Test48(arg0, 8) == 0) ? 0x10 : 0xF;
            }
        }
        BtlAnim_SetBlend(D_00386640, arg0, var_a1);
        return func_0023C710(arg0);
    }
    return -1;
}
