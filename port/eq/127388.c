#include "common.h"

void func_00128278(void *arg0, void *arg1);
void func_001283A0(void *arg0);
extern u8 *D_003876A0;
extern u8 *gEftHitList;

void func_00127388(void) {
    s32 temp_v1;
    s32 var_s1;
    s32 var_s2;
    u8 *temp_a1;
    u8 *temp_s0;
    u8 *temp_v0;
    u8 *temp_v1_2;
    u8 *var_a0;

    if (gEftHitList == NULL) {
        return;
    }
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        temp_a1 = gEftHitList;
        var_a0 = temp_a1;
        var_s2 = 0;
        if (*(s32 *)(var_a0 + 0x6000) > 0) {
            var_s1 = 0;
            do {
                temp_s0 = var_a0 + var_s1;
                temp_v0 = *(u8 **)(temp_s0 + 0x60);
                if (temp_v0 != NULL) {
                    temp_v1 = *(s32 *)(temp_v0 + 4);
                    if (!(temp_v1 & 0x200) && !(*(s32 *)(temp_s0 + 0x50) & 2) && !(temp_v1 & 0x20)
                        && (temp_v1 & 0x3F)) {
                        if (*(s32 *)(temp_s0 + 0x68) != 0) {
                            func_00128278(temp_s0, temp_a1);
                        }
                        if (*(s32 *)(temp_s0 + 0x64) != 0) {
                            func_001283A0(temp_s0);
                        }
                        temp_v1_2 = *(u8 **)(temp_s0 + 0x60);
                        *(s32 *)(temp_v1_2 + 4) = *(s32 *)(temp_v1_2 + 4) | 0x200;
                    }
                }
                var_a0 = temp_a1;
                var_s2 += 1;
                var_s1 += 0x180;
            } while (var_s2 < *(s32 *)(var_a0 + 0x6000));
        }
    }
}
