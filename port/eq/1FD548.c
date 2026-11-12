#include "common.h"

s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0023F410(u8 *arg0);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
s32 BtlObjXf_Update(u8 *arg0);
s32 func_001FA3A8(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(void *arg0);
u32 func_00212320(u8 *arg0);
s32 func_00241C98(u8 *arg0, u32 arg1);
void func_00212DD8(u8 *arg0, s32 arg1);
extern f32 D_00385860;

s32 func_001FD548(u8 *arg0, u8 *arg1) {
    u8 fr[0x30];
    u8 *temp_s0;
    u8 *pb;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_v0_2;

    var_v0 = func_00211310(arg0, 3, 0x80000);
    if (var_v0 == 0) {
        return 0;
    }
    var_v0 = 0;
    if (func_0023F410(arg1) & 0x20000) {
        return 0;
    }
    if (func_0023F410(arg1) & 0x10000) {
        if (*(s32 *)(*(u8 **)(arg1 + 0x1530) + 8) == 0) {
            if (*(u8 *)(BtlMember_GetActiveGauge(arg1) + 0x28) == 0) {
                return 0;
            }
        }
    }

    func_00208DE8(*(s32 *)(arg0 + 0x1534), fr, 3);
    func_00208DE8(*(s32 *)(arg1 + 0x1534), fr + 0x10, 3);
    func_00312650(fr + 0x20, fr, fr + 0x10);
    if (100.0f < func_0029DFD0(fr + 0x20)) {
        return 0;
    }

    temp_v0 = func_001FA3A8(BtlObjXf_Update(arg1));
    if (temp_v0 & 0x100000) {
        if (temp_v0 & 0x01000000) {
            return 0;
        }
    } else {
        temp_s0 = BtlChar_GetPos(arg0);
        pb = BtlChar_GetPos(arg1);
        if (fabsf(BtlUtil_WrapAngle(*(f32 *)(temp_s0 + 0xB4) - *(f32 *)(pb + 0xB4))) < D_00385860) {
            return 0;
        }
    }

    var_s0 = 0x96;
    temp_v0_2 = func_00212320(arg0);
    if (temp_v0_2 < 2U) {
        var_s0 = func_00241C98(arg0, temp_v0_2);
    }
    *(s32 *)(arg1 + 0xB8C) = var_s0;
    *(s32 *)(arg1 + 0xB90) = var_s0 * 2;
    func_00212DD8(arg1, 0);
    var_v0_2 = (temp_v0 & 0x100000) ? 0xD : 3;
    *(s32 *)(arg1 + 0xB48) = var_v0_2;
    var_v0 = 1;
    return var_v0;
}
