#include "common.h"

extern u8 *gBtlStage;

u8 *func_002768D8(s32 arg0) {
    u8 *var_v0;
    u8 *temp_a1;

    var_v0 = NULL;
    if (gBtlStage != NULL) {
        temp_a1 = *(u8 **)(gBtlStage + 4);
        if (temp_a1 != NULL) {
            var_v0 = temp_a1 + (*(s32 *)(temp_a1 + 8) * 4) + (arg0 << 5);
        }
    }
    return var_v0;
}
