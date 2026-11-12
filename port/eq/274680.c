#include "m2c_macros.h"

extern u8 *gBtlStage;

s32 func_00274680(s32 arg0) {
    u8 *ent;
    s32 var_v0 = 0;

    ent = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(gBtlStage + 0x48) * 4 + arg0 * 0x50;
    if ((*(s32 *)ent & 1) == 0) {
        var_v0 = *(s32 *)(ent + 0x34);
    }
    return var_v0;
}
