#include "common.h"

s32 func_002E0F68(void *arg0, s32 arg1);
void StgSlot_Call12(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void StgSlot_Call13(s32 arg0, s32 arg1, s32 arg2);
void StgSlot_Call14(s32 arg0, s32 arg1, void *arg2);
void func_002E08F8(void *arg0);
s32 func_002E11E8(s32 arg0, s32 arg1);

s32 func_002E0830(u8 *arg0, s32 arg1) {
    u8 *var_s0;
    s32 var_a2;
    s32 var_s2;
    s32 var_v0;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_t0;

    var_s2 = 0;
    if (func_002E0F68(arg0, arg1) != 0) {
        var_s0 = arg0 + 0x3BC;
        var_a2 = *(s32 *)var_s0;
        do {
            temp_a1 = var_s2;
            temp_a3 = *(s32 *)(var_s0 + 4);
            temp_t0 = *(s32 *)(var_s0 + 8);
            var_s2 += 1;
            var_s0 += 0xC;
            StgSlot_Call12(*(s32 *)(arg0 + 0x3B4), temp_a1, var_a2, temp_a3, temp_t0);
            if (var_s2 < 4) {
                var_a2 = *(s32 *)var_s0;
            }
        } while (var_s2 < 4);
        StgSlot_Call13(*(s32 *)(arg0 + 0x3B4), *(s32 *)(arg0 + 0x3EC), *(s32 *)(arg0 + 0x3F0));
        var_v0 = -2;
        if (func_002E11E8(*(s32 *)(arg0 + 0x3B4), arg1) == 0) {
            StgSlot_Call14(*(s32 *)(arg0 + 0x3B4), 0, arg0 + 0x3F4);
            func_002E08F8(arg0);
            return 0;
        }
        return var_v0;
    }
    return -1;
}
