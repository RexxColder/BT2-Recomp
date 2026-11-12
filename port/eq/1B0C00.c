#include "common.h"

extern u8 *D_00387858;

void func_001B0C00(u8 *arg0) {
    u8 *temp_a3;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;
    u8 *var_a1;
    s32 var_a2;

    temp_a3 = *(u8 **)(arg0 + 0x38);
    var_a2 = 0;
    temp_v0 = D_00387858 + (*(s32 *)(temp_a3 + 0x44) * 4) + 0xCC;
    var_a1 = *(u8 **)temp_v0;
    while (var_a1 != NULL) {
        if (*(s32 *)var_a1 == (s32)arg0) {
            temp_v1 = *(u8 **)(var_a1 + 8);
            temp_v0_2 = *(u8 **)(var_a1 + 4);
            if (temp_v1 == NULL) {
                *(u8 **)temp_v0 = temp_v0_2;
            } else {
                *(u8 **)(temp_v1 + 4) = temp_v0_2;
            }
            if (*(u8 **)(var_a1 + 4) != NULL) {
                *(u8 **)(*(u8 **)(var_a1 + 4) + 8) = *(u8 **)(var_a1 + 8);
            } else {
                *(u8 **)(D_00387858 + (*(s32 *)(temp_a3 + 0x44) * 4) + 0xD4) = *(u8 **)(var_a1 + 8);
            }
            *(u8 **)(var_a1 + 8) = NULL;
            *(s32 *)var_a1 = 0;
            *(u8 **)(var_a1 + 4) = NULL;
            *(s32 *)(D_00387858 + (*(s32 *)(temp_a3 + 0x44) * 4) + 0xDC) -= 1;
            return;
        }
        var_a2 += 1;
        var_a1 = *(u8 **)(var_a1 + 4);
        if (var_a2 >= 0x10) {
            return;
        }
    }
}
