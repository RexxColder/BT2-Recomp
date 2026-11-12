#include "common.h"

extern u8 *gEftMod1CBMgr;

u8 *func_001C95C8(u8 *arg0) {
    s32 temp_a1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_a3;
    u8 *base;

    var_a3 = 0;
    var_a2 = 0;
    var_a1 = *(s32 *)(gEftMod1CBMgr + 4);
loop_1:
    base = *(u8 **)gEftMod1CBMgr;
    temp_v0 = base + var_a1 * 0x140;
    if (*(s32 *)temp_v0 != 0) {
        temp_a1 = var_a1 + 1;
        var_a2 += 1;
        var_a1 = (temp_a1 >= 0x12C) ? 0 : temp_a1;
        if (var_a2 < 0x12C) {
            goto loop_1;
        }
    } else {
        var_a3 = temp_v0;
        *(s32 *)(var_a3 + 0x130) = 0;
        *(s32 *)(var_a3 + 0x134) = 0;
        *(s32 *)(gEftMod1CBMgr + 4) = var_a1 + 1;
        if (*(s32 *)(gEftMod1CBMgr + 4) >= 0x12C) {
            *(s32 *)(gEftMod1CBMgr + 4) = 0;
        }
    }
    if (var_a3 != 0) {
        if (*(u8 **)arg0 == 0) {
            *(u8 **)arg0 = var_a3;
        }
        temp_v0_2 = *(u8 **)(arg0 + 4);
        if (temp_v0_2 != 0) {
            *(u8 **)(var_a3 + 0x134) = temp_v0_2;
            *(u8 **)(*(u8 **)(arg0 + 4) + 0x130) = var_a3;
        }
        *(u8 **)(arg0 + 4) = var_a3;
    }
    return var_a3;
}
