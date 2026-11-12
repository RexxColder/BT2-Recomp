#include "common.h"

s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void BtlAnim_SetBlend(f32 farg0, u8 *arg1);
s32 func_00212320(u8 *arg0);
s32 func_00217488(u8 *arg0);
s32 func_002411E0(u8 *arg0, s32 arg1);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023C710(u8 *arg0, s32 arg1);
extern f32 D_00386928;
extern f32 D_0038692C;

s32 func_002338B8(u8 *arg0) {
    s32 v;

    if (func_00211310(arg0, 4, 0x04000000) != 0) {
        BtlAnim_SetBlend(D_00386928, arg0);
        v = func_00217488(arg0);
        if (v == 0xAD) {
            return 0xCE;
        }
        if (v < 0xAE) {
            if (v == 0xAC) {
                return 0xCD;
            }
        } else if (v == 0xAE) {
            return 0xCF;
        }
        goto block_11;
    }
block_11:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_0038692C, arg0);
    if (func_002411E0(arg0, func_00212320(arg0)) & 0x200000) {
        func_002113C0(arg0, 1, 0x40000, 1);
        func_002113C0(arg0, 1, 0x80000, 1);
        func_002113C0(arg0, 2, 0x1000, 1);
        return 0x21;
    }
    return func_0023C710(arg0, 1);
}
