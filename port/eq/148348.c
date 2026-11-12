#include "common.h"

s32 BtlCharApi_IsInTechnique(s32 arg0);
s32 func_00126560(void);
s32 func_0020A9C0(s32 arg0);
extern u8 *D_00387760;

void func_00148348(void) {
    s32 temp_a0;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    u8 *temp_s0;

    if (D_00387760 == NULL) {
        return;
    }
    if (func_00126560() == 0) {
        var_s1 = 0;
        if (*(s32 *)(D_00387760 + 8) > 0) {
            var_s2 = 0;
            var_v0 = *(s32 *)(D_00387760 + 4);
loop_3:
            temp_s0 = (u8 *)(var_v0 + var_s2);
            var_s2 += 0x270;
            temp_a0 = var_s1;
            var_s1 += 1;
            if ((BtlCharApi_IsInTechnique(temp_a0) == 0) && (func_0020A9C0(temp_a0) == 0)) {
                *(s32 *)(temp_s0 + 0x260) = -1;
            }
            if (var_s1 < *(s32 *)(D_00387760 + 8)) {
                var_v0 = *(s32 *)(D_00387760 + 4);
                goto loop_3;
            }
        }
    }
}
