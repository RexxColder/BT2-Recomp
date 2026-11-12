#include "common.h"

extern u8 *gEftPtcl4Mgr;

s32 func_001BCB48(void *arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    var_t1 = 0;
    var_t2 = 0;
    var_a3 = *(s32 *)(gEftPtcl4Mgr + 4);
loop_2:
    temp_v1 = *(u8 **)(gEftPtcl4Mgr + 0) + (var_a3 << 8);
    if (*(s32 *)temp_v1 != 0) {
        var_a0 = var_a3 + 1;
        goto block_13;
    }
    *(s32 *)(temp_v1 + 0xE8) = 0;
    *(s32 *)(temp_v1 + 0xEC) = 0;
    *(s32 *)(temp_v1 + 0xF0) = 0;
    *(u8 **)(temp_v1 + 0xF4) = NULL;
    if (*(u8 **)((u8 *)arg0 + 0xE8) == NULL) {
        *(u8 **)((u8 *)arg0 + 0xE8) = temp_v1;
    }
    temp_v0 = *(u8 **)((u8 *)arg0 + 0xEC);
    if (temp_v0 != NULL) {
        *(u8 **)(temp_v1 + 0xF4) = temp_v0;
        *(u8 **)(*(u8 **)((u8 *)arg0 + 0xEC) + 0xF0) = temp_v1;
    }
    *(u8 **)((u8 *)arg0 + 0xEC) = temp_v1;
    var_a0 = var_a3 + 1;
    *(s32 *)(gEftPtcl4Mgr + 4) = var_a0;
    if (*(s32 *)(gEftPtcl4Mgr + 4) >= 0xC8) {
        *(s32 *)(gEftPtcl4Mgr + 4) = 0;
    }
    var_t1 += 1;
    *(s32 *)(gEftPtcl4Mgr + 8) = *(s32 *)(gEftPtcl4Mgr + 8) + 1;
    if (var_t1 < arg1) {
block_13:
        var_t2 += 1;
        var_a3 = (var_a0 >= 0xC8) ? 0 : var_a0;
        if (var_t2 >= 0xC8) {
            var_v0 = 0;
            if (var_t1 >= arg1) {
                goto block_15;
            }
        } else {
            goto loop_2;
        }
    } else {
block_15:
        *(s8 *)((u8 *)arg0 + 6) = (s8)arg1;
        var_v0 = 1;
    }
    return var_v0;
}
