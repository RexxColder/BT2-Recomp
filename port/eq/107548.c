#include "common.h"

extern u8 *gObjOutline;

void func_00107548(s32 *arg0, s32 arg1, s32 arg2) {
    u8 sp[16];
    s32 temp_a1;
    s32 var_s2;
    s32 temp_v0;
    u8 var_s1;
    u8 *var_s0;

    temp_a1 = arg1 << 5;
    var_s0 = (u8 *)(*arg0) + temp_a1;
    var_s2 = arg2 & 0xFF;
    if (*(s32 (**)(u8 *, s32))(var_s0 + 0xC) != NULL) {
        var_s1 = var_s0[0x1A];
        if (var_s1 == 1) {
            *(s32 *)(sp + 0) = (s32)arg0;
            *(s32 *)(sp + 4) = *(s32 *)(var_s0 + 4);
            *(s32 *)(sp + 8) = *(s32 *)(var_s0 + 0x10);
            sp[0xC] = (var_s0[0x1B] == 0);
            sp[0xD] = var_s0[0x1C];
            temp_v0 = (*(s32 (**)(u8 *, s32))(var_s0 + 0xC))(sp, temp_a1);
            if (temp_v0 == var_s1) {
                var_s0[0x1A] = 0;
            }
            var_s0[0x1B] = var_s1;
            var_s0[0x1C] = 0;
            if (var_s2 != 0) {
                gObjOutline[4] = (u8)temp_v0;
            }
        }
    }
}
