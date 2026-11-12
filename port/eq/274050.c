#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
extern u8 *gBtlStage;

s32 func_00274050(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_a3;
    s32 var_v0;
    u8 *temp_a2;

    var_v0 = 0;
    temp_a3 = arg2 * 0x10;
    if (*(s32 *)((u8 *)arg1 + 0x34) & 0x20000000) {
        temp_a2 = *(u8 **)(gBtlStage + 4);
        temp_a1 = *(s32 *)(temp_a2 + temp_a3 + *(s32 *)(temp_a2 + 0xC) * 4 + 0xC);
        func_003126C8(arg0, (s32)(temp_a2 + ((((temp_a1 < 0) ? (temp_a1 + 3) : temp_a1) >> 2) * 4)));
        var_v0 = 1;
    }
    return var_v0;
}
