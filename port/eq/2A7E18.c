#include "common.h"

s32 Gsc_GetInt(s32 arg0);
extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002A7E18(s32 arg0) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    u8 *temp_s0;
    u8 *temp_a0;

    temp_s0 = D_003B26B0 + 0x2B0;
    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt(arg0);
        var_a0 = 0;
        if (*(s32 *)(D_003B26B0 + 0x2B0) == temp_v0) {
            var_a0 = 1;
        } else {
            for (var_a1 = 1; var_a1 < 5; var_a1++) {
                if (*(s32 *)(temp_s0 + (var_a1 * 0x10)) == temp_v0) {
                    var_a0 = 1;
                    break;
                }
            }
        }
        if (var_a0 == 0) {
            if (*(s32 *)(D_003B26B0 + 0x2B0) == 0) {
                *(s32 *)(D_003B26B0 + 0x2B0) = temp_v0;
            } else {
                for (var_a1_2 = 1; var_a1_2 < 5; var_a1_2++) {
                    temp_a0 = temp_s0 + (var_a1_2 * 0x10);
                    if (*(s32 *)temp_a0 == 0) {
                        *(s32 *)temp_a0 = temp_v0;
                        break;
                    }
                }
            }
        }
    }
    return 1;
}
