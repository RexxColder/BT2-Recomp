#include "common.h"

void BtlTask_SetDead(u8 *arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);

void func_00148B70(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_a1;
    s32 *temp_v1;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_a1 = *(u8 **)(temp_s0 + 4);
    if (temp_a1 != NULL) {
        temp_v1 = *(s32 **)(temp_a1 + 0x20);
        if (temp_v1 != NULL) {
            if (*temp_v1 == 0xBE) {
                EftShot_TestBits(*(s32 *)temp_a1, 4);
                if ((EftShot_TestBits(*(s32 *)*(u8 **)(temp_s0 + 4), 8) != 0) ||
                    (EftShot_TestBits(*(s32 *)*(u8 **)(temp_s0 + 4), 0x80) != 0)) {
                    BtlTask_SetDead(arg0);
                }
            } else {
                BtlTask_SetDead(arg0);
            }
            return;
        }
        BtlTask_SetDead(arg0);
        return;
    }
    BtlTask_SetDead(arg0);
}
