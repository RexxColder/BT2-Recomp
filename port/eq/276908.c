#include "common.h"

extern u8 *gBtlStage __attribute__((section(".data")));

s32  func_00276908(s32 arg0) {
    u8 var_v0;
    u8 *temp_a1;

    var_v0 = 0;
    if (gBtlStage != NULL) {
        temp_a1 = *(u8 **)(gBtlStage + 4);
        if (temp_a1 != NULL) {
            var_v0 = *(u8 *)(temp_a1 + *(s32 *)(temp_a1 + 8) * 4 + (arg0 << 5));
        }
    }
    return (u8)(var_v0);
}
