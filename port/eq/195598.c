#include "common.h"

void EftPtcl3_SetPos(s32 arg0, void *arg1);
void func_0018BB50(s32 arg0, void *arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern u8 *D_003877D0;

void func_00195598(void) {
    u8 *temp_a0;
    u8 *temp_s0;
    u8 *temp_s1;
    s32 var_s2;
    s32 var_s3;

    temp_a0 = D_003877D0 + 0xA0;
    if (*(s32 *)(D_003877D0 + 0xA0) != 0) {
        *(s32 *)(temp_a0 + 0x10C) = 0;
    }
    if (*(s32 *)(temp_a0 + 0x120) != 0) {
        *(s32 *)(temp_a0 + 0x22C) = 0;
    }
    var_s3 = 0;
    var_s2 = 1;
    do {
        temp_s0 = D_003877D0 + var_s3;
        var_s3 += 0x50;
        temp_s1 = temp_s0 + 0x20;
        if (*(s32 *)(temp_s0 + 8) != 0) {
            func_00208DE8(*(s32 *)(temp_s0 + 0), temp_s1, *(s32 *)(temp_s0 + 0xC));
            if (*(s32 *)(temp_s0 + 4) == 0) {
                EftPtcl3_SetPos(*(s32 *)(temp_s0 + 0x40), temp_s1);
                func_0018BB50(*(s32 *)(temp_s0 + 0x44), temp_s1);
            }
        }
        var_s2 -= 1;
    } while (var_s2 >= 0);
}
