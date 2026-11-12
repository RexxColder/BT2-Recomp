#include "common.h"

s32 func_001EBD90(s32 arg0, s32 arg1);
extern s32 D_00387898;

void func_001C20D8(s32 arg0) {
    s16 var_s0;
    s32 temp_s1;
    s32 temp_v0;

    temp_s1 = *(s32 *)(*(s32 *)(D_00387898 + 4) + 0x38);
    var_s0 = *(s16 *)(temp_s1 + 0xF406);
    for (;;) {
        var_s0 = (s16)(var_s0 - 1);
        temp_v0 = func_001EBD90(temp_s1 + 0xF400, (s32)var_s0);
        if (temp_v0 == 0) {
            return;
        }
        if (*(u16 *)(temp_v0 + 0xD2) == (u16)(arg0 & 0xFFFF)) {
            return;
        }
    }
}
